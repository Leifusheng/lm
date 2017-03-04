#include "../lm_def.h"
#include "../Json.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/epoll.h>

int epollfd;
int control_ui;
int control_other;
int control_filetransmit;
string myname;

typedef struct user_t
{
    string name;
    string ip;
};

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

int control_create_socket(uint16_t port)
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = 0;
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    return fd;
}

void control_init()
{
    epollfd = epoll_create(512);
    control_ui = control_create_socket(CONTROL_UI_PORT);
    control_other = control_create_socket(CONTROL_OTHER_PORT);
    control_filetransmit = control_create_socket(CONTROL_FILETRANSMIT_PORT);

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
    if (cmd == LM_SETNAME)
    {
        string name = json.value(LM_NAME);
        myname = name;
        printf("set name is %s\n", name.c_str());
        //save name
        //broadcast my name
        control_broadcast(json);
    }
}

void control_handle_other()
{
    struct sockaddr_in addr;
    socklen_t socklen = sizeof(addr);
    char buf[2048];
    recvfrom(control_ui, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &socklen);
    Json json;
    json.parse(buf);
    string cmd = json.value(LM_CMD);
    if (cmd == LM_SETNAME)
    {
        //1.check this is new user
        string name = json.value(LM_NAME);
        string ip = inet_ntoa(addr.sin_addr);
        user_t* user = control_find_user(ip);
        if (user == NULL)
        {
            control_add_user(ip, name);
        }
        else
        {
            user->name = name;
        }

        Json json_resp;
        json_resp.add(LM_CMD, LM_SETNAME_ACK);
        json_resp.add(LM_NAME, myname);
    }
    else if (cmd == LM_SETNAME_ACK)
    {
        string name = json.value(LM_NAME);
        //user_t*
    }

}

void control_handle__filetransmit()
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
                    control_handle__filetransmit();
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
