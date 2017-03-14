#include "../lm_def.h"
#include "../Json.h"
#include "../lm_public.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <algorithm>
using namespace std;


int epollfd;
int control_ui;
int control_other;
int control_filetransmit;
int token = 0;

string myname;
list<string> ips;

typedef struct user_t
{
    string name;
    string ip;
}user_t;

static map<string, user_t*> users;

user_t* control_find_user(string ip)
{
    auto it = users.find(ip);
    if (it == users.end())
        return NULL;
    return it->second;
}


void control_add_user(string ip, string name)
{
    user_t *user = new user_t;
    user->ip = ip;
    user->name = name;
    users[ip] = user;
}


void control_send(Json& json, u_int16_t port, string ip = "255.255.255.255")
{
    string buf = json.print();
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    sendto(control_other, buf.c_str(), buf.size(), 0, (struct sockaddr*)&addr, sizeof(addr));
}

void control_init()
{
    //get local ip list
    ips = get_ip_addrs();
    //token create
    srand(time(NULL));

    epollfd = epoll_create(512);
    control_ui = create_udp_socket(CONTROL_UI_PORT);
    control_other = create_udp_socket(CONTROL_OTHER_PORT);
    control_filetransmit = create_udp_socket(CONTROL_FILETRANSMIT_PORT);

    //set control other broadcast function
    int optval = 1;
    setsockopt(control_other, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));
    //add socket to epoll
    struct epoll_event ev;
    ev.data.fd = control_ui;
    ev.events = EPOLLIN;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, control_ui, &ev);

    ev.data.fd = control_filetransmit;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, control_filetransmit, &ev);

    //std input
    ev.data.fd = control_other;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, control_other, &ev);
}

void control_broadcast(Json& json)
{
    string buf = json.print();
    struct sockaddr_in addr;
    addr.sin_port = htons(CONTROL_OTHER_PORT);
    addr.sin_addr.s_addr = inet_addr("255.255.255.255");
    addr.sin_family = AF_INET;
    sendto(control_other, buf.c_str(), buf.size(), 0, (struct sockaddr*)&addr, sizeof(addr));
}

void control_handle_ui()
{
    char buf[2048];
    recv(control_ui, buf, sizeof(buf), 0);
    Json json;
    json.parse(buf);
    string cmd = json.value(LM_CMD);
    printf("ctrl handle ui %s", buf);
    if (cmd == LM_SETNAME)
    {
        string name = json.value(LM_NAME);
        myname = name;
        printf("set name is %s\n", name.c_str());
        //save name
        //broadcast my name
        control_broadcast(json);
    }
    else if (cmd == LM_LIST)
    {
        //send all user info to ui
        for (auto it = users.begin(); it != users.end(); it++)
        {
            user_t* user = it->second;
            Json json;
            json.add(LM_CMD, LM_LIST_ACK);
            json.add(LM_IP, user->ip);
            json.add(LM_NAME, user->name);
            control_send(json, UI_CONTROL_PORT, "127.0.0.1");
        }
    }
    else if (cmd == LM_TO)
    {
        /*
         * json.add(LM_CMD, LM_TO);
        json.add(LM_RECV, recvip);
        json.add(LM_MSG, msg);
        */
        string toip = json.value(LM_RECV);
        json.add(LM_BY, myname);
        if (toip == "255.255.255.255")
        {
            json.add(LM_IS_BROADCAST, 1);
        }
        else
            json.add(LM_IS_BROADCAST, 0);

        control_send(json, CONTROL_OTHER_PORT, toip);
        //string content = json.value(LM_MSG);
    }
    else if(cmd == LM_SENDFILE)
    {
        /*
         * cmd sendfile
         * recv:ip
         * filepath: .....
        */
        string toip = json.value(LM_RECV);
        string path = json.value(LM_FILEPATH);

        /*
         * cmd ft
         * filepath: xxx
         * recv:ip
         * type:send
         * token:xxxx
         * FILELEN: file length
         * ref:
        */
        //get file status
        struct stat stat_buf;
        stat(path.c_str(), &stat_buf);

        int token = rand();
        Json task_json;
        task_json.add(LM_CMD, LM_FILETRANSMIT);;
        task_json.add(LM_FILEPATH, path);
        task_json.add(LM_RECV, toip);
        task_json.add(LM_TYPE, LM_SEND);
        task_json.add(LM_TOKEN, token);
        task_json.add(LM_FILELEN, (int)stat_buf.st_size);
        if (toip == "255.255.255.255")
            task_json.add(LM_REF, users.size());
        else
            task_json.add(LM_REF, 1);
        control_send(task_json, FT_CONTROL_PORT, "127.0.0.1");
        usleep(1000);

        //send message to user,let he recive file
        Json notify_json;
        notify_json.add(LM_CMD, LM_FILETRANSMIT);
        notify_json.add(LM_TOKEN, token);
        notify_json.add(LM_FILELEN, (int)stat_buf.st_size);
        notify_json.add(LM_FROM_NAME, myname);
        control_send(notify_json, CONTROL_OTHER_PORT, toip);
    }
    else if (cmd == LM_FILETRANSMIT)
    {
        control_send(json, FT_CONTROL_PORT, "127.0.0.1");
    }

}


void control_handle_other()
{
    struct sockaddr_in addr;
    socklen_t socklen = sizeof(addr);
    char buf[2048];
    recvfrom(control_other, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &socklen);
    Json json;
    json.parse(buf);
    string cmd = json.value(LM_CMD);
    string ip = inet_ntoa(addr.sin_addr);
    
    printf("ip %s cmd %s\n", ip.c_str(), cmd.c_str());
    if (find(ips.begin(), ips.end(), ip) != ips.end())
    {
        return;
    }
    if(myname.size() == 0)
    {
        return;
    }

    if (cmd == LM_SETNAME)
    {
        //1.check this is new user
        string name = json.value(LM_NAME);

        user_t* user = control_find_user(ip);
        if (user == NULL)
        {
            //if new user add to map
            control_add_user(ip, name);
            //send my info to the new user
            Json json_resp;
            json_resp.add(LM_CMD, LM_SETNAME_ACK);
            json_resp.add(LM_NAME, myname);
            control_send(json_resp, CONTROL_OTHER_PORT, ip);
        }
        else
        {
            //modify name
            user->name = name;
        }
        user = control_find_user(ip);
        //notify other some one enter
        Json resp;
        resp.add(LM_CMD, LM_LIST_ACK);
        resp.add(LM_IP, user->ip);
        resp.add(LM_NAME, user->name);
        control_send(resp, UI_CONTROL_PORT, "127.0.0.1");
    }
    else if (cmd == LM_SETNAME_ACK)
    {
        string name = json.value(LM_NAME);
        user_t* user = control_find_user(ip);
        if (user == NULL)
        {
            //add new user
            control_add_user(ip, name);
        }
        else
        {
            user->name = name;
        }
        user = control_find_user(ip);
        //notify other some one enter
        Json resp;
        resp.add(LM_CMD, LM_LIST_ACK);
        resp.add(LM_IP, user->ip);
        resp.add(LM_NAME, user->name);
        control_send(resp, UI_CONTROL_PORT, "127.0.0.1");
        printf("control send end\n");
    }
    else if (cmd == LM_TO)
    {
        printf("to buf %s\n", json.print().c_str());
        /*
         * json.add(LM_CMD, LM_TO);
        json.add(LM_RECV, recvip);
        json.add(LM_MSG, msg);
        json.add(LM_BY, myname);
        */
        printf("1\n");
        string msg = json.value(LM_MSG);
        printf("2\n");
        string by = json.value(LM_BY);
        //send content to ui
        printf("3\n");
        Json toui;
        printf("4\n");
        toui.add(LM_CMD, LM_MSG);
        printf("5\n");
        toui.add(LM_FROM_NAME, by);
        printf("6\n");
        toui.add(LM_FROM_IP, ip);
        printf("7\n");
        toui.add(LM_MSG, msg);
        printf("control send start\n");
        toui.add(LM_IS_BROADCAST, json.value(LM_IS_BROADCAST));
        control_send(toui, UI_CONTROL_PORT, "127.0.0.1");
        printf("control send end\n");
    }
    else if (cmd == LM_FILETRANSMIT)
    {
        /*
         *notify_json.add(LM_TOKEN, token);
        notify_json.add(LM_FILELEN, (int)stat_buf.st_size);
        notify_json.add(LM_FROM_NAME, myname);
        */
        //send task to ui ask user recv or not
        Json ui_json;
        ui_json.add(LM_CMD, LM_FILETRANSMIT);
        //who send file to me
        ui_json.add(LM_SEND, ip);
        ui_json.add(LM_TYPE, LM_RECV);
        ui_json.add(LM_TOKEN, json.value(LM_TOKEN));
        ui_json.add(LM_FILELEN, json.value(LM_FILELEN));
        ui_json.add(LM_FROM_NAME, json.value(LM_FROM_NAME));
        control_send(ui_json, UI_CONTROL_PORT, "127.0.0.1");
    }

}

void control_handle_filetransmit()
{

}

void control_run()
{
    struct epoll_event ev;
    while(1)
    {
        int ret = epoll_wait(epollfd, &ev, 1, 5000);
        if (ret > 0)
        {
            printf("control ui %d\n", control_ui);
            printf("control other %d\n", control_other);
            printf("control filetransmit %d\n", control_filetransmit);

            printf("fd is %d\n", ev.data.fd);
            //ui send message
            if (ev.data.fd == control_ui)
            {
                control_handle_ui();
            }
            //othre send message
            else if (ev.data.fd == control_other)
            {
                control_handle_other();
            }
            //filetransmit send message
            else if (ev.data.fd == control_filetransmit)
            {
                control_handle_filetransmit();
            }
        }
    }
}

int main()
{
    control_init();
    control_run();
    return 0;
}
