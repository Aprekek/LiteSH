#ifndef CLIESERV_C
#define CLIESERV_C

#include "Clieserv.h" 

clients *Clients[MAX_CLIENT];


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

int Sendto(int sockfd, const void *buf, size_t len, int flags, struct sockaddr *addr, socklen_t addrlen)
{
    int res = sendto(sockfd, buf, len, flags, addr, addrlen);
    if (res < 0)
        perror("Sendto failed\n");
    return res;
}

int Recv(int sockfd, void *buf, size_t len, int flags)
{
    int res = recv(sockfd, buf, len, flags);
    if (res < 0)
        perror("resvfrom failed\n");
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

void str_trim_lf (char* arr, int length) 
{
  for (int i = 0; i < length; i++)
    if (arr[i] == '\n') 
    {
      arr[i] = '\0';
      break;
    }
  
}

void AddInQueue(clients *cl)
{
    pthread_mutex_lock(&clientsMutex);

    for (int i = 0; i < MAX_CLIENT; i++)
        if (!Clients[i])
        {
            Clients[i] = cl;
            break;
        }


    pthread_mutex_unlock(&clientsMutex);
}

void QueueRemove(int uid)
{
    pthread_mutex_lock(&clientsMutex);

    for (int i = 0; i < MAX_CLIENT; i++)
        if (Clients[i])
            if (Clients[i]->uid == uid)
            {
                Clients[i] = NULL;
                break;
            }
    pthread_mutex_unlock(&clientsMutex);
}

int Pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arq)
{
    int res = pthread_create(thread, attr, start_routine, arq);
    if (res != 0)
    {
        perror("pthread_create failed\n");
        exit(1);
    }
    return res;
}

void *handleClient(void *arg)
{
    char buf[Buffer_size];
    char name[NAME_LEN];
    int leaveFlags;

    cliCount++;
    clients *cli = (clients *)arg;

    if(recv(cli->sockfd, name, NAME_LEN, 0) <= 0 || strlen(name) <  2 || strlen(name) >= NAME_LEN-1)
    {
		printf("Didn't enter the name.\n");
		leaveFlags = 1;
	} 
    else
    {
		strcpy(cli->name, name);
		sprintf(buf, "%s has joined\n", cli->name);
		printf("%s", buf);
		sendMessage(buf, cli->uid);
	}

	bzero(buf, Buffer_size);

    while(1)
    {
        //Туточки будет код взаимодействия клиента с сервером
    }

    close(cli->sockfd);
    QueueRemove(cli->uid);
    free(cli);
    cliCount--;
    pthread_detach(pthread_self());

    return 0;

}
