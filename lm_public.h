#ifndef LM_PUBLIC_H
#define LM_PUBLIC_H

int create_udp_socket(uint16_t port)
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = 0;
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    return fd;
}
#endif // LM_PUBLIC_H
