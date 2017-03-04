#include "../lm_def.h"
#include "../lm_public.h"
#include "../socket.h"
#include "../Json.h"
#include <list>
using namespace std;

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

list<lm_task_t*> lm_tasks;
list<lm_task_t*> lm_complete_tasks;

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
            lm_tasks.push_back(task);
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
            lm_tasks.push_back(task);
        }
    }
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
                //ft_handle__server();
            }
        }
    }
}


int main()
{
    filetransmit_init();
    filetransmit_run();
    return 0;
}
