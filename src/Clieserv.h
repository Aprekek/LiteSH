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

#include "process.h"

#define MAX_MSG_LENGTH 256

static int cliCount = 0;
static int uid = 10;

typedef struct 
{
    struct sockaddr_in addres;
    int sockfd;
} clients;

// Help function
void showMenu();
void printArguments();
void printReadme();
void Help();

int Socket(int domain, int type, int protocol);
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Listen(int sockfd, int backlog);
int Accept(int sickfd, struct sockaddr *addr, socklen_t *addrlen);
void Connect(int socket, const struct sockaddr *addr, socklen_t addrlen);
int Pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arq);
void *handleClient(void *arg);

#endif
