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
/*
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
*/
void printIpAddr(struct sockaddr_in addr)
{
    printf("%d.%d.%d.%d", 
            addr.sin_addr.s_addr & 0xff,
            (addr.sin_addr.s_addr & 0xff00) >> 8,
            (addr.sin_addr.s_addr & 0xff0000) >> 16,
            (addr.sin_addr.s_addr & 0xff000000) >> 24);
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
    //lab3
    char *strH, *strHelp, *strLab2, *strProc, *strProcBg, *strSignal;
    strHelp = "--help";
    strH = "-h";
    strLab2 = "-l2";
    strProc = "-p";
    strProcBg = "-pb";
    strSignal = "-signal";
   //lab2
    char *strMoving, *strCopy, *strDelete, *strSize, *strAllFiles, *strAllProc;
    strMoving = "-m";
    strCopy = "-c";
    strDelete = "-d";
    strSize = "-s";
    strAllFiles = "-af";
    strAllProc = "-ap";
    
    char buf[MAX_MSG_LENGTH];
    char buf1[MAX_MSG_LENGTH];
    char buf2[MAX_MSG_LENGTH];
    char buf3[3];
    while(1)
    {
        recv(connfd,buf, MAX_MSG_LENGTH,0);
        if (buf == strHelp || buf == strH) // Help
            Help(); 
        else if (strcmp(buf, strLab2)) {
            if (launchLab2() != 0)
                puts("Error\n");
        }
        else if(strcmp(buf, strProc)) {
            if (spawnProcess() != 0)
                 puts("Error\n");
        }
        else if (strcmp(buf, strProcBg)) {
            if (spawnProcessFone() != 0)
                puts("Error\n");
        }
        else if (strcmp(buf, strSignal)) {
            catchSignal();   
        }
        else if (strcmp(buf, strMoving))
        { // Перемещение файла;
            puts ("Enter file name or path to file: \n");
            recv(connfd,buf2, MAX_MSG_LENGTH,0);
            cout << "Enter path to dir moving: ";
            recv(connfd,buf3, MAX_MSG_LENGTH,0);
            moveFile(buf2, buf3);

        } else if (strcmp(buf, strCopy))  { // Копирование файла;
            cout << "Enter file name or path to file: ";
            recv(connfd,buf2, MAX_MSG_LENGTH,0);
            cout << "Enter path to dir copy: ";
            recv(connfd,buf3, MAX_MSG_LENGTH,0);
            copyFile(buf2, buf3);

        } else if (strcmp(buf, strDelete))  { // Удаление файла;
            cout << "Enter file name or path to file: ";
            recv(connfd,buf2, MAX_MSG_LENGTH,0);
            deleteFile(buf2);
        } else if (strcmp(buf, strSize))  { // Подсчет общего размера указанной директории или файла;
            cout << "File or Dir" << endl;
            cout << "If file - enter 'f'" << endl;
            cout << "If dir - enter 'd'" << endl;
            recv(connfd,buf3, 3,0);

            if (buf3 == "f") {
                puts("Enter file name or path to file: ");
                 recv(connfd,buf2, MAX_MSG_LENGTH,0);
                cout << getFileSize(buf2) << " Byte" << endl;
            } else if (buf3 == "d") {
                cout << "Enter path to the dir: ";
                recv(connfd,buf2, MAX_MSG_LENGTH,0);
                cout << getDirSize(buf2) << " Byte" << endl;
            } else {
                cout << "Incorrect arguments" << endl;
            }

        } else if (strcmp(buf, strAllFiles))  { // Отображение всех файлов в указанной директории;
            cout << "Enter path to the dir: ";
            recv(connfd,buf2, MAX_MSG_LENGTH,0);
            displayAllFiles(buf2);

        } else if  (strcmp(buf, strAllProc))  { // Отображение всех процессов из файловой системы procfs.
            displayProc();
        }
        else {
            puts("Error\n");
            return 0;
        }

        bzero(buf, MAX_MSG_LENGTH);
    }

    close(cli->sockfd);
    free(cli);
    pthread_detach(pthread_self());

    return 0;

}
