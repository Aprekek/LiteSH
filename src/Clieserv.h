#ifndef CLIESERV_H
#define CLIESERV_H

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
//#include <signal.h>

#define Buffer_size 2048

typedef struct 
{
    struct sockaddr_in addres;
    int sockfd;
    int uid;
    char name [NAME_LEN];
} clients;



static int cliCount = 0;
static int uid = 10;

int Socket(int domain, int type, int protocol);
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Listen(int sockfd, int backlog);
int Accept(int sickfd, struct sockaddr *addr, socklen_t *addrlen);
void Connect(int socket, const struct sockaddr *addr, socklen_t addrlen);
void Inet_pton(int af, const char *src, void *dst);
void printIpAddr(struct sockaddr_in addr);


#endif
