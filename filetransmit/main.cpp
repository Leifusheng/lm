#include "../lm_def.h"
#include "../lm_public.h"
#include "../socket.h"
#include "../Json.h"
#include "../lm_autolock.h"
#include <list>
#include <algorithm>
using namespace std;

pthread_mutex_t mutex;
int ft_server; //tcp server accept
int ft_control;//udp control to file transmit
int ft_ui;  //check file send progress
int maxfd;
fd_set set;

typedef struct lm_task_t
{
    string path;
    string ip;
    string type;
    string token;
    int filelen;
    int ref;
    int file_transmit_len;
}lm_task_t;

list<lm_task_t*> lm_recvs;
map<string, lm_task_t*> lm_sends;
list<lm_task_t*> lm_complete_tasks;

void *recv_thread(void *ptr)
{
    lm_task_t* recvtask = (lm_task_t*)ptr;
    int sock = connect_server(recvtask->ip.c_str(), FT_SERVER_PORT);
    int total_len = recvtask->filelen;
    FILE* fp = fopen(recvtask->path.c_str(), "w");

    char buf[1024];
    //send token
    int token = atoi(recvtask->token.c_str());
    token = htonl(token);
    doSend(sock, (char *)&token, sizeof(token));

    while (1)
    {
        int ret = recv(sock, buf, sizeof(buf), 0);
        if (ret > 0)
        {
            fwrite(buf, ret, 1, fp);
            recvtask->file_transmit_len += ret;
        }
        else if (ret <= 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            break;
        }
    }
    {
        lm_autolock lock(mutex);
        auto it = find(lm_recvs.begin(), lm_recvs.end(), recvtask);
        if (it != lm_recvs.end())
            lm_recvs.erase(it);
        lm_complete_tasks.push_back(recvtask);
    }
    fclose(fp);
    close(sock);
}

void filetransmit_init()
{
    ft_control = create_udp_socket(FT_CONTROL_PORT);
    ft_ui = create_udp_socket(FT_UI_PORT);
    ft_server = create_server(FT_PORT, "127.0.0.1", 250);
    maxfd = ft_server;
    //add socket to I/O select
    FD_ZERO(&set);
    FD_SET(ft_control, &set);
    FD_SET(ft_ui, &set);
    FD_SET(ft_server, &set);
}


void ft_handle_control()
{
    char buf[2048];
    recv(ft_control, buf, sizeof(buf), 0);
    Json json;
    json.parse(buf);
    string cmd = json.value(LM_CMD);
    if (cmd == LM_FILETRANSMIT)
    {
        //send or recive file
        /*
         * task_json.add(LM_CMD, LM_FILETRANSMIT);;
        task_json.add(LM_FILEPATH, path);
        task_json.add(LM_RECV, toip);
        task_json.add(LM_TYPE, LM_SEND);
        task_json.add(LM_TOKEN, token);
        task_json.add(LM_FILELEN, (int)stat_buf.st_size);
        task_json.add(LM_REF, users.size());
        */
        string type = json.value(LM_TYPE);
        if (type == LM_SEND)
        {
            //add task
            lm_task_t* task = new lm_task_t;

            task->path = json.value(LM_FILEPATH);
            task->ip = json.value(LM_RECV);
            task->token = json.value(LM_TOKEN);
            task->filelen = atoi(json.value(LM_FILELEN).c_str());
            task->ref = atoi(json.value(LM_REF).c_str());
            printf("task ref=%d, toip:%s type:%s\n",
                   task->ref, task->ip.c_str(), task->type.c_str());
            lm_autolock lock(mutex);
            lm_sends[task->token] = task;
        }
        else if (type == LM_RECV)
        {
            /*
             *  ui_json.add(LM_CMD, LM_FILETRANSMIT);
                ui_json.add(LM_SEND, ip);
                ui_json.add(LM_TYPE, LM_RECV);
                ui_json.add(LM_TOKEN, json.value(LM_TOKEN));
                ui_json.add(LM_FILELEN, json.value(LM_FILELEN));
                ui_json.add(LM_FROM_NAME, json.value(LM_FROM_NAME));
                json.add(LM_ACK, LM_YES);
                json.add(LM_LOCAL_PATH, "/home/saul/Desktop/lm/test.file");
            */
            lm_task_t* task = new lm_task_t;
            task->filelen = atoi(json.value(LM_FILELEN).c_str());
            task->ip = json.value(LM_SEND);
            task->path = json.value(LM_LOCAL_PATH);
            task->token = json.value(LM_TOKEN);
            task->type = type;
            task->ref = 1;
            task->file_transmit_len = 0;
            printf("ready to recv file:%s\n", task->path.c_str());
            lm_autolock lock(mutex);
            lm_recvs.push_back(task);
            //create recive thread
            pthread_t tid;
            pthread_create(&tid, NULL, recv_thread, task);
            pthread_detach(tid);
        }
    }
}

void *send_thread(void* ptr)
{
    int fd = (intptr_t)ptr;
    //recive token
    int token;
    if (doRecv(fd, (char *)&token, 4) != 4)
    {
        close(fd);
        return NULL;
    }
    token = ntohl(token);
    //send file
    char buf[1024];
    sprintf(buf, "%d", token);
    string key = buf;
    lm_task_t* task_send;
    {
        lm_autolock lock(mutex);
        if (lm_sends.find(key)!= lm_sends.end())
        {
            close(fd);
            return NULL;
        }
        task_send = lm_sends[key];
    }
    FILE *fp = fopen(task_send->path.c_str(), "r");
    //send file
    while(1)
    {
        int ret = fread(buf, 1, sizeof(buf), fp);
        if (ret > 0)
        {
            if (doSend(fd, buf, ret) != ret)
            {
                break;
            }
        }
        else
            break;
    }
    {
        lm_autolock lock(mutex);
        lm_sends.erase(key);
        lm_complete_tasks.push_back(task_send);
    }
    close(fd);
    fclose(fp);
}

void ft_handle__server()
{
    int newfd = accept(ft_server, NULL, NULL);
    //create pthread
    pthread_t tid;
    pthread_create(&tid, NULL, send_thread, (void *)(intptr_t)&newfd);
    pthread_detach(tid);
}

void filetransmit_run()
{
    while(1)
    {
        fd_set check_set;
        memcpy(&check_set, &set, sizeof(set));
        struct timeval tv;
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        int ret = select(maxfd + 1, & check_set, NULL, NULL, &tv);

        if (ret > 0)
        {
            if (FD_ISSET(ft_control, &check_set))
            {
                ft_handle_control();
            }
            else if (FD_ISSET(ft_ui, &check_set))
            {
                //ft_handle_ui();
            }
            else if (FD_ISSET(ft_server, &check_set))
            {
                ft_handle__server();
            }
        }
    }
}


int main()
{
    lm_mutex_init(mutex);
    filetransmit_init();
    filetransmit_run();
    return 0;
}
