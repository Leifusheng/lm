#include <netinet/in.h>
#include <sys/epoll.h>
#include <stdio.h>
#include "../lm_def.h"
#include "../Json.h"
#include <arpa/inet.h>
#include <string.h>


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
int main()
{
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
