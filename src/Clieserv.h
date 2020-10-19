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

#include "/src/help.cpp"
#include "/src/litesh.cpp"
#include "/filesystem/src/filesystem.cpp"

#define MAX_MSG_LENGTH 256

pthread_mutex_t clientsMutex = PTHREAD_MUTEX_INITIALIZER;

static int cliCount = 0;
static int uid = 10;

typedef struct 
{
    struct sockaddr_in addres;
    int sockfd;
    int uid;
    char name [NAME_LEN];
} clients;


int Socket(int domain, int type, int protocol);
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Listen(int sockfd, int backlog);
int Accept(int sickfd, struct sockaddr *addr, socklen_t *addrlen);
void Connect(int socket, const struct sockaddr *addr, socklen_t addrlen);
int Pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arq);

#endif
