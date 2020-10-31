#include "Clieserv.h"
#include "process.h"
bool flag = 0;


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


void SendClient(void *arg, char *file)
{
    FILE *fp;
    clients *cli = (clients *)arg;
    int counter = 512;
    fp = fopen(file, "w");
    char *buffer = calloc(sizeof(char) * (counter+1)); 

    while(!feof(fp))
    {
        fgets(buffer);
        write(cli->sockfd, buffer , strlen(buffer));
    }

}


void *handleClient(void *arg, void *arg1)
{  
    char *path = "output.txt";
    clients *cli = (clients *)arg;
    comArg *comar = (comArg *)arg1;

    //lab3
    // "--help" "-h"; "-l2"; "-p"; strProcBg = "-pb"; "-signal"; "-m"; "-c"; "-d"; "-s"; "-af"; "-ap";
    while(flag == 0)
    {
        if (strcmp(comar->buf, "-h") == 0)
        {
            int fp = open(path, O_WRONLY | O_APPEND);
	        dup2(fp, 1);
            Help();
        } 

        else if(strcmp(comar->buf, "-p") == 0) 
        {
            int status = 0;
            pid_t pid;
            pid = fork();

            if (pid == 0) 
            {
                dup2(cli->sockfd, 1)
                execl(comar->buf1, comar->buf1, NULL);
            } else if (pid < 0)
                status = -1;
            else if (waitpid(pid, &status, 0) != pid)
                status = -1;
            FILE *fp;
            fp = open(path,  O_WRONLY | O_APPEND);
            fprintf(fp, "%d", status);
            fclose(fp);

        }
        
        else if (strcmp(comar->buf, "-pb") == 0) 
        {
            int status = 0;
            pid_t pid;
            pid = fork();

            if (pid == 0) 
            {
                dup2(cli->sockfd, 1)
                execl(comar->buf1, omar->buf1, NULL);
                _exit (EXIT_FAILURE);
            } else if (pid < 0)
                status = -1;
            else if (waitpid(pid, &status, WNOHANG) != 0)
                status = -1;
            FILE *fp;
            fp = open(path,  O_WRONLY | O_APPEND);
            fprintf(fp, "%d", status);
            fclose(fp);

        }
        else if (strcmp(comar->buf, "-sig") == 0) 
        {
            //FIXME
            catchSignal();
             
        }
        else if (strcmp(comar->buf, "-m") == 0) 
        { // Перемещение файла;
            moveFile(comar->buf1, comar->buf2);
              
        } 
        else if (strcmp(comar->buf, "-c") == 0)  
        { // Копирование файла;
            copyFile(comar->buf1, comar->buf2);
              
        } 
        else if (strcmp(comar->buf, "-d") == 0)  
        { // Удаление файла;
            deleteFile(comar->buf1);
             
        } 
        else if (strcmp(comar->buf, "-s") == 0)  
        { // Подсчет общего размера указанной директории или файла;
            if (comar->buf3 == "f") 
            {
                printGetFileSize(comar->buf2, path);
                 
            } 
            else if (comar->buf3 == "d") 
            {
                printGetDirSize(comar->buf2, path);
                 
            } else 
            {
               flag = 1;
            }

        } 
        else if (strcmp(comar->buf, "-af") == 0)  
        { // Отображение всех файлов в указанной директории;
            displayAllFiles(comar->buf2, path);
             
        } 
        else if  (strcmp(comar->buf, "-ap") == 0)  
        { // Отображение всех процессов из файловой системы procfs.
            displayProc(path);
           
        }
        else 
        {
            flag = 1;
        }
        

    }
    SendClient(cli, path);
    close(cli->sockfd);
    free(cli);
    free(comar);
    pthread_detach(pthread_self());

    return 0;

}

