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

/*int Pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arq)
{
    int res = pthread_create(thread, attr, start_routine, arq);
    if (res != 0)
    {
        perror("pthread_create failed\n");
        exit(1);
    }
    return res;
}*/


void SendClient(void *arg, char *file)
{
    FILE *fp;
    clients *cli = (clients *)arg;
    int counter = 512;
    fp = fopen(file, "w");
    char *buffer = (char *)calloc((counter+1), sizeof(char)); 

    while(!feof(fp))
    {
        fgets(buffer, counter, fp);
        write(cli->sockfd, buffer, strlen(buffer));
    }

}

/*
void *handleClient(void *arg, struct comArg comArg)
{  
 	clients *cli = (clients *)arg;
	bool flag = 0;
    char *path = "output.txt";                
        
    //lab3
    // "--help" "-h"; "-l2"; "-p"; strProcBg = "-pb"; "-signal"; "-m"; "-c"; "-d"; "-s"; "-af"; "-ap";
    while(flag == 0)
    {
        if (strcmp(comArg.buf, "-h") == 0)
        {
            int fp = open(path, O_WRONLY | O_APPEND);
	        dup2(fp, 1);
           printf("Help \n");
        } 

        else if(strcmp(comArg.buf, "-p") == 0) 
        {
            int status = 0;
            pid_t pid;
            pid = fork();

            if (pid == 0) 
            {
                dup2(cli->sockfd, 1);
                execl(comArg.buf1, comArg.buf1, NULL);
            } else if (pid < 0)
                status = -1;
            else if (waitpid(pid, &status, 0) != pid)
                status = -1;
            FILE * fp;
            fp = fopen(path, "w");
            fprintf(fp, "%d", status);
            fclose(fp);

        }
        
        else if (strcmp(comArg.buf, "-pb") == 0) 
        {
            int status = 0;
            pid_t pid;
            pid = fork();

            if (pid == 0) 
            {
                dup2(cli->sockfd, 1);
                execl(comArg.buf1, comArg.buf1, NULL);
                exit (EXIT_FAILURE);
            } else if (pid < 0)
                status = -1;
            else if (waitpid(pid, &status, WNOHANG) != 0)
                status = -1;
            FILE * fp;
            fp = fopen(path,  "w");
            fprintf(fp, "%d", status);
            fclose(fp);
        }
        else if (strcmp(comArg.buf, "-sig") == 0) 
        {
            //FIXME
            catchSignal();
             
        }
        else if (strcmp(comArg.buf, "-m") == 0) 
        { // Перемещение файла;
            moveFile(comArg.buf1, comArg.buf2);
              
        } 
        else if (strcmp(comArg.buf, "-c") == 0)  
        { // Копирование файла;
            copyFile(comArg.buf1, comArg.buf2);
              
        } 
        else if (strcmp(comArg.buf, "-d") == 0)  
        { // Удаление файла;
            deleteFile(comArg.buf1);
             
        } 
        else if (strcmp(comArg.buf, "-s") == 0)  
        { // Подсчет общего размера указанной директории или файла;
            if (strcmp(comArg.buf3,"f")) 
            {
                getFileSize(comArg.buf2, path);
                 
            } 
            else if (strcmp(comArg.buf3, "d")) 
            {
                printGetDirSize(comArg.buf2, path);
                 
            } else 
            {
               flag = 1;
            }

        } 
        else if (strcmp(comArg.buf, "-af") == 0)  
        { // Отображение всех файлов в указанной директории;
            displayAllFiles(comArg.buf2, path);
             
        } 
        else if  (strcmp(comArg.buf, "-ap") == 0)  
        { // Отображение всех процессов из файловой системы procfs.
            displayProc(path);
           
        }
        else 
        {
            flag = 1;
        }
        

    }
    SendClient(cli, path);
	path = "The end";
	write(cli->sockfd, path, strlen(path));
    close(cli->sockfd);
    free(cli);
    pthread_detach(pthread_self());

    return 0;

}
*/