#ifndef CLIESERV_H
#define CLIESERV_H

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>

#include "filesystem.h"

#define MSG_LENGTH 512
#define SizeBufRecv 1024*1024 
#define SizeBufSend 1024


struct clients 
{
    int count;
    int sockfd;
};

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
void getArg(char *operation, int count, char **param);
int SendClient(int cli, char *file);

#endif
