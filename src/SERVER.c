#include "Clieserv.h"   

void sig_child(int sig) //--функция ожидания завершения дочернего процесса
{
    pid_t pid;
    int stat;
    while ((pid = waitpid(-1,&stat,WNOHANG)) > 0)
    {
    }
    return;
}


int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        perror("ERROR, no port provided\n");
        printf ("Enter arg\n");
        exit(1);
    }
    char *buf[256];
    comArg comArg;
    if (argc == 3)
    {
        for(int i = 0; i < strlen(argv[2]); i++)
            comArg.buf[i] = argv[2][i];
      
    }
    
    if (argc == 4)
    {
        for(int i = 0; i < strlen(argv[2]); i++)
            comArg.buf[i] = argv[2][i];
        for(int i = 0; i < strlen(argv[3]); i++)
            comArg.buf[i] = argv[3][i];
     
    }
    else if (argc == 5)
    {
        for(int i = 0; i < strlen(argv[2]); i++)
            comArg.buf[i] = argv[2][i];

        for(int i = 0; i < strlen(argv[3]); i++)
            comArg.buf1[i] = argv[3][i];

        for(int i = 0; i < strlen(argv[4]); i++)
            comArg.buf2[i] = argv[4][i];
    }

    else if (argc == 6)
    {
        for(int i = 0; i < strlen(argv[2]); i++)
            comArg.buf[i] = argv[2][i];

        for(int i = 0; i < strlen(argv[3]); i++)
            comArg.buf1[i] = argv[3][i];

        for(int i = 0; i < strlen(argv[4]); i++)
            comArg.buf2[i] = argv[4][i];
        
        for(int i = 0; i < strlen(argv[4]); i++)
            comArg.buf2[i] = argv[4][i];
    }
   
    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);
    int connfd = 0;
    struct sockaddr_in serverAdr = {0};
    struct sockaddr_in clientAddr = {0};
    pthread_t tid;

    int server = Socket(AF_INET, SOCK_STREAM, 0); //протокол
    serverAdr.sin_family = AF_INET;
    serverAdr.sin_addr.s_addr = inet_addr(ip);
    serverAdr.sin_port = htons(port);

    Bind(server, (struct sockaddr *) &serverAdr, sizeof serverAdr);

    Listen(server, 1);

    socklen_t clieLen = sizeof(clientAddr);

    //dup2(connfd,1);
  	
    printf("%d\n", strlen(comArg.buf));
    signal(SIGCHLD,sig_child);
    connfd = Accept(server, (struct sockaddr *) &clientAddr, &clieLen);
    clients cli;
	cli.addres = clientAddr;
	cli.sockfd = connfd;
    pid_t pid; 
    char re[2];
    char buff[256];
    
    if((pid = fork()) == 0)
    {
        close(server);
        handleClient(cli, comArg);
    }             
	
    close(cli.sockfd);
    close(server);
    return 0;
}
