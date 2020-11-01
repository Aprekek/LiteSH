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
    if (argc != 2)
    {
        perror("ERROR, no port provided\n");
        exit(1);
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
  	
    while(1)
    {
        signal(SIGCHLD,sig_child);
        connfd = Accept(server, (struct sockaddr *) &clientAddr, &clieLen);
        clients *cli = (clients *)malloc(sizeof(clients));
	    cli->addres = clientAddr;
	    cli->sockfd = connfd;
        pid_t pid; 
        struct comArg comArg;
        
        if((pid = fork()) == 0)
        {
            close(server);
            char count[6];
            while(1)
            {
                int nbytes = read(cli->sockfd, count, 5); 
                strncat(count, "\0", 1); 
                printf("%d\n", nbytes);

                if(strcmp(count, "1") == 0) 
                {
                    recv(cli->sockfd, comArg.buf, MAX_MSG_LENGTH,0);
                    printf("%s", comArg.buf);
              
                }
                
                else if(strcmp(count, "2") == 0) 
                {
                    recv(cli->sockfd,comArg.buf, 3, 0);
                    recv(cli->sockfd,comArg.buf1, MAX_MSG_LENGTH,0);
                    printf("hello2\n");
             
                }
            
                else if(strcmp(count, "3") == 0) 
                {   
                    recv(cli->sockfd,comArg.buf, 3, 0);
                    recv(cli->sockfd,comArg.buf1, MAX_MSG_LENGTH,0);
                    recv(cli->sockfd,comArg.buf2, MAX_MSG_LENGTH,0);
                    printf("hello3\n");
                
                }

                else if(strcmp(count, "4") == 0) 
                {
                    recv(cli->sockfd,comArg.buf, 3, 0);
                    recv(cli->sockfd,comArg.buf1, MAX_MSG_LENGTH,0);
                    recv(cli->sockfd,comArg.buf3, 3,0);
                    recv(cli->sockfd,comArg.buf2, MAX_MSG_LENGTH,0);
                    printf("hello4\n");
                
                }
                else
                {
                    exit (EXIT_FAILURE);
                
                }

                
            }
            

            //handleClient((void *)cli, comArg);
        }
       
                
            

    }
	
    close(connfd);
    close(server);
    return 0;
}
