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

int SendClient(int cli, char *file)
{
    FILE *fp;
    long int size = SizeBufRecv;
    int counter = MSG_LENGTH ;
    fp = fopen(file, "r");

    if(fp == 0)
    {
        perror("Error: open file for sending");
        return -1;
    }

    char *buff = (char *)malloc((counter+1) * sizeof(char));
    char *buffer = (char *)malloc(size *sizeof(char));

    while(!feof(fp))
    {
        fgets(buff, counter, fp);
        strcat(buffer, buff);
    }
    fclose(fp);
    write(cli, buffer, strlen(buffer));
    free(buff);
    free(buffer);

    return 0;
}


void getArg(char *operation, int count, char **param)
{
    char sep [10]=" ";
    char *istr = (char *)malloc(MSG_LENGTH* sizeof(char));

    if (count > 1)
    {
        for (int i = 1; i < count; i++)
        {
            istr = strtok(operation,sep);

            for (int j = 0; j < strlen(istr); j++)
                param[i][j] = istr[j];
        }
    }
    else
        param[1] = operation;

}


void *handleClient(void *arg)
{
    clients *cli = (clients *)arg;
    char *operation = (char *)malloc(SizeBufSend * sizeof(char));
    char *errorBuf = (char *)malloc(MSG_LENGTH * sizeof(char));
    char *op = (char *)malloc(MSG_LENGTH * sizeof(char));

    while ((read(cli->sockfd, operation, MSG_LENGTH)) != -1) {
        int file;
        /*получение количества аргументов*/
        int count = atoi(&operation[0]);

        char **param = (char **)malloc(count * sizeof(char));

        for (int i = 0; i < count; i++)
            param[i] = (char *)malloc(SizeBufSend* sizeof(char));

        for (int j = 0; j < strlen(operation) - 3; j++)
            op[j] = operation[j + 2];

        file = open("itog.txt",  O_WRONLY | O_APPEND);

        if (file == -1) {
            errorBuf = "error open file\n";
            if ((write(cli->sockfd, errorBuf, strlen(errorBuf))) == -1)
                exit(1);
        }
      
        getArg(op, count, param);
        dup2(file, 1);
     
        startProg(count, param);
     

        close (file);
        // free(errorBuf);

        if (SendClient(cli->sockfd, "itog.txt") == -1) {
            errorBuf = "error open file\n";
            if ((write(cli->sockfd, errorBuf, strlen(errorBuf))) == -1)
                exit(1);
        }

        free(errorBuf);
        remove ("itog.txt");
        dup2(0, STDOUT_FILENO);
        close(cli->sockfd);
        free(cli);
        pthread_detach(pthread_self());

        bzero(operation, MSG_LENGTH);
    }

    return 0;
}
