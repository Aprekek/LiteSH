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
	int counter = 512;
    fp = fopen(file, "r");
	
    if(fp == 0)
    {
        perror("Error: open file for sending");
        return -1;
    }

    char *buff = (char *)calloc((size, sizeof(char));
	char *buffer = (char *)calloc((counter + 1, sizeof(char)); 

    while(!feof(fp))
    {
        fgets(buff, counter, fp);
        strcat(buffer, buff);
    }
    close(fp);
	write(cli, buffer, strlen(buffer));
	free(buff);
	free(buffer);

    return 0;
}


char **getArg(char *arg, int count)
{
    char sep [10]=" ";
    char *istr; 

	char **istr1 = (char **)calloc(count, sizeof(char));
   
    for(int i = 0; i < count; i++)
        istr1[i] = (char *)calloc(256, sizeof(char));

    for (int i = 1; i < count; i++)
    {
		istr = strtok (arg,sep);
        for (int j = ; j < strlen(istr); j++)
            istr1[i][j] = istr[j];
    }

    return istr1;

}


void *handleClient(void *arg)
{  
    clients *cli = (clients *)arg;
    char *operation = (char *) calloc(SizeBufRecv, sizeof (char)); 
    char *Buf = (char *) calloc(SizeBufRecv, sizeof (char)); 
    char *errorBuf = (char *) calloc(MSG_LENGTH, sizeof (char)); 
    char **param;
    
    while ((nread = read(cli->sockfd, operation, MSG_LENGTH))!= -1)
    {
        int file;
        /*получение количества аргументов*/
        cli->count = operation[0];
        
        for (int j = 0; j < strlen(operation)-2; j++)
            operation[j] = operation[j + 2] 

        
        if ((file = open("itog.txt", O_RDWR | O_TRUNC | O_APPEND)) = -1)
        {
            errorBuf = "error open file\n";
            if ((write(cli->sockfd, errorBuf, strlen(errorBuf))) == -1)
                exit(1);
        }
        dup2(file, STDOUT_FILENO);

        param = getArg(operation, cli->count);

        startProg(cli->count, param);

        close (file);
        free(errorBuf);

        if (SendClient(cli->sockfd, "itog.txt") == -1)
        {
            errorBuf = "error open file\n";
            if ((write(cli->sockfd, errorBuf, strlen(errorBuf))) == -1)
                exit(1);
        }
        
        free(errorBuf);

        dup2(0, STDOUT_FILENO);
        close(cli->sockfd);
        free(cli);
        pthread_detach(pthread_self());

        bzero(operation, MSG_LENGTH);
        free(errorBuf);

    }
    

    return 0;

}
/*
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
    
    char bufCopy[MAX_MSG_LENGTH];
    char buf[MAX_MSG_LENGTH];
    char buf1[MAX_MSG_LENGTH];
    char buf2[MAX_MSG_LENGTH];
    char buf3[3];
    while(1)
    {
        recv(cli->sockfd,bufCopy, MAX_MSG_LENGTH,0);
        for (int i = 0; i < strlen(bufCopy) - 1; i++) 
            buf[i] = bufCopy[i];
        
        if (strcmp(buf, strH) == 0) // Help
            //Help();
            puts("Hello\n");
        else if (strcmp(buf, strLab2) == 0) {
            if (launchLab2() != 0)
                puts("Error\n");
        }
        else if(strcmp(buf, strProc) == 0) {
            if (spawnProcess() != 0)
                 puts("Error\n");
        }
        else if (strcmp(buf, strProcBg) == 0) {
            if (spawnProcessFone() != 0)
                puts("Error\n");
        }
        else if (strcmp(buf, strSignal) == 0) {
            catchSignal();   
        }
        else if (strcmp(buf, strMoving) == 0) { // Перемещение файла;
            puts ("Enter file name or path to file!: \n");
            recv(cli->sockfd,buf2, MAX_MSG_LENGTH,0);
            cout << "Enter path to dir moving: ";
            recv(cli->sockfd,buf3, MAX_MSG_LENGTH,0);
            moveFile(buf2, buf3);

        } else if (strcmp(buf, strCopy) == 0)  { // Копирование файла;
            cout << "Enter file name or path to file: ";
            recv(cli->sockfd,buf2, MAX_MSG_LENGTH,0);
            cout << "Enter path to dir copy: ";
            recv(cli->sockfd,buf3, MAX_MSG_LENGTH,0);
            copyFile(buf2, buf3);

        } else if (strcmp(buf, strDelete) == 0)  { // Удаление файла;
            cout << "Enter file name or path to file: ";
            recv(cli->sockfd,buf2, MAX_MSG_LENGTH,0);
            deleteFile(buf2);
        } else if (strcmp(buf, strSize) == 0)  { // Подсчет общего размера указанной директории или файла;
            cout << "File or Dir" << endl;
            cout << "If file - enter 'f'" << endl;
            cout << "If dir - enter 'd'" << endl;
            recv(cli->sockfd,buf3, 3,0);

            if (buf3 == "f") {
                puts("Enter file name or path to file: ");
                 recv(cli->sockfd,buf2, MAX_MSG_LENGTH,0);
                cout << getFileSize(buf2) << " Byte" << endl;
            } else if (buf3 == "d") {
                cout << "Enter path to the dir: ";
                recv(cli->sockfd,buf2, MAX_MSG_LENGTH,0);
                cout << getDirSize(buf2) << " Byte" << endl;
            } else {
                cout << "Incorrect arguments" << endl;
            }

        } else if (strcmp(buf, strAllFiles) == 0)  { // Отображение всех файлов в указанной директории;
            cout << "Enter path to the dir: ";
            recv(cli->sockfd,buf2, MAX_MSG_LENGTH,0);
            displayAllFiles(buf2);

        } else if  (strcmp(buf, strAllProc) == 0)  { // Отображение всех процессов из файловой системы procfs.
            displayProc();
        }
        else {
            puts("Error\n");
            return 0;
        } 
    }   
*/
