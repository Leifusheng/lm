#include <netinet/in.h>
#include <sys/epoll.h>
#include <stdio.h>
#include "../lm_def.h"
#include "../Json.h"
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//#include "../lm_public.h"


int epollfd;
int ui_control;
int ui_filetransmit;


void ui_init()
{
    epollfd = epoll_create(512);
    ui_control = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = 0;
    addr.sin_port = htons(UI_CONTROL_PORT);
    addr.sin_family = AF_INET;
    bind(ui_control, (struct sockaddr*)&addr, sizeof(addr));
    ui_filetransmit = socket(AF_INET, SOCK_DGRAM, 0);
    addr.sin_port = htons(UI_FILETRANSMIT_PORT);
    bind(ui_filetransmit, (struct sockaddr*)&addr, sizeof(addr));

    //add socket to epoll
    struct epoll_event ev;
    ev.data.fd = ui_control;
    ev.events = EPOLLIN;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, ui_control, &ev);

    ev.data.fd = ui_filetransmit;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, ui_filetransmit, &ev);

    //std input
    ev.data.fd = 0;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, 0, &ev);
}


void ui_send_control(Json &json)
{
    string packet = json.print();
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(CONTROL_UI_PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("%s\n", packet.c_str());
    sendto(ui_control, packet.c_str(), packet.size(), 0, (struct sockaddr*)&addr, sizeof(addr));
}

void ui_handle_cmd(char *buf)
{
    char* cmd = strtok(buf, " ");
    if (strcmp(cmd, LM_SETNAME) == 0)
    {
        /*
            *send json to control
            * cmd: setname
            * name: frank
        */
        Json obj;
        obj.add(LM_CMD, LM_SETNAME);
        obj.add(LM_NAME, strtok(NULL, "\0"));

        //send json to ui
        ui_send_control(obj);
    }
    else if (strcmp(cmd, LM_LIST) == 0)
    {
        //user ask user list
        Json obj;
        obj.add(LM_CMD, LM_LIST);

        //send json to ui
        ui_send_control(obj);
    }
    else if (strcmp(cmd, LM_TO) == 0)
    {
        /*
         * to ip:content
         * to all:content  to 255.255.255.255:content
         * json
         * {
         * cmd to
         * recv ip
         * msg content
         * }
        */
        string recvip = strtok(NULL, ":");
        string content = strtok(NULL, "\0");
        Json json;
        json.add(LM_CMD, LM_TO);
        json.add(LM_RECV, recvip);
        json.add(LM_MSG, content);
        ui_send_control(json);
    }
    else if (strcmp(cmd, LM_SENDFILE) == 0)
    {
        char* recvip = strtok(NULL, ":");
        char* path = strtok(NULL, "\0");

        //get realpath from sample path
        char realpath_bk[256];
        if (realpath(path, realpath_bk) == NULL)
        {
            printf("patj error!\n");
            return;
        }
        //query file exist or not
        struct stat stat_buf;
        if (stat(realpath_bk, &stat_buf) < 0)
        {
            printf("file not exist\n!");
            return;
        }
        //query file can access or not
        if (access(realpath_bk, R_OK) < 0)
        {
            printf("file can not access!\n");
            return;
        }
        /*
         * cmd sendfile
         * recv:ip
         * filepath: .....
        */
        Json json;
        json.add(LM_CMD, LM_SENDFILE);
        json.add(LM_RECV, recvip);
        json.add(LM_FILEPATH, realpath_bk);
        ui_send_control(json);
    }

}

void ui_handle_user_input()
{
    char buf[1024];
    fgets(buf, sizeof(buf), stdin);
    buf[strlen(buf) - 1] = 0;
    if (strlen(buf) == 0)
        return;
    //setname frank
    printf("%s/n", buf);
    ui_handle_cmd(buf);
}

void ui_get_message_from_control()
{
    char buf[2048];
    recv(ui_control, buf, sizeof(buf), 0);
    Json json;
    json.parse(buf);
    string cmd = json.value(LM_CMD);
    if (cmd == LM_LIST_ACK)
    {
        //user ask user list
        string ip = json.value(LM_IP);
        string name = json.value(LM_NAME);
        printf("user ip = %s, user name is %s \n", ip.c_str(), name.c_str());
    }
    else if (cmd == LM_MSG)
    {
        string msg = json.value(LM_MSG);
        string fromname = json.value(LM_FROM_NAME);
        string fromip = json.value(LM_FROM_IP);
        printf("%s(%s) say: %s \n", fromname.c_str(), fromip.c_str(), msg.c_str());
    }
    else if (cmd == LM_FILETRANSMIT)
    {
        printf("%s send a file to me, filelen = %d", json.value(LM_FROM_NAME).c_str()
               , json.value(LM_FILELEN).c_str());
        json.add(LM_ACK, LM_YES);
        json.add(LM_LOCAL_PATH, "/home/saul/Desktop/lm/test.file");
        ui_send_control(json);
    }
}

void ui_get_message_from_filetransmit()
{

}

void ui_run()
{
    struct epoll_event ev;
    while(1)
    {
        int ret = epoll_wait(epollfd, &ev, 1, 5000);
        if (ret > 0)
        {
            if (ev.data.fd == 0)
            {
                ui_handle_user_input();
            }
            else if (ev.data.fd == ui_control)
            {
                ui_get_message_from_control();
            }
            else if (ev.data.fd == ui_filetransmit)
            {
                ui_get_message_from_filetransmit();
            }
        }
    }
}

/*
    *1.get user input
    *
*/
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("argument error!");
        return 0;
    }
    //get argument
    char *control_path = argv[1];
    char *ft_path = argv[2];
    //start control
    pid_t pid = fork();
    if (pid == 0)
    {
        execl(control_path, control_path, NULL);
        printf("start control error!\n");
        return 0;
    }
    pid = fork();
    if (pid == 0)
    {
       execl(ft_path, ft_path, NULL);
       printf("start filetransmit error!\n");
       return 0;
    }
    /*
        *create sockets
        * create epoll
    */
    ui_init();
    /*
        *epoll wait
    */
    ui_run();
}
