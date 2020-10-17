#include "Clieserv.h"


int Socket(int domain, int type, int protocol)
{
    int res = socket(domain, type, protocol);
    if (res == -1)
    {
        perror("socket failed\n");
        exit(1);
    }
    return res;

}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int res = bind(sockfd, addr, addrlen);
    if (res == -1)
    {
        perror("bind failed\n");
        exit(1);
    }
}

void Listen(int sockfd, int backlog)
{
    int res = listen(sockfd, backlog);
     if (res == -1)
    {
        perror("listen failed");
        exit(1);
    }

}

int Accept(int sickfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int res = accept(sickfd, addr, addrlen);
    if (res == -1)
    {
        perror("accept failed\n");
        exit(1);
    }
    return res;
}


void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int res = connect(sockfd, addr, addrlen);
    if (res == -1)
    {
        perror("connect failed\n");
        exit(1);
    }
}

void Inet_pton(int af, const char *src, void *dst)
{
    int res = inet_pton(af, src, dst);
    if (res == 0)
    {
        printf("inet_pton failed: src does not contain a character strling representing a valid network addres in specified addres family\n");
        exit(1);
    }
    if (res == -1)
    {
        perror("inet_pton failed\n");
        exit(1);
    }
}
int Write(int handle, void *buf, int count)
{
    int res = write (handle, buf, count);
    if(res < count || res < 0)
        {
            perror("write failed\n");
            exit(1);
        }
    return res;
}

void printIpAddr(struct sockaddr_in addr)
{
    printf("%d.%d.%d.%d", 
            addr.sin_addr.s_addr & 0xff,
            (addr.sin_addr.s_addr & 0xff00) >> 8,
            (addr.sin_addr.s_addr & 0xff0000) >> 16,
            (addr.sin_addr.s_addr & 0xff000000) >> 24);
}
