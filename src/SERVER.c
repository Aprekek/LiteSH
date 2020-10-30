#include "Clieserv.h"
#include "filesystem.h" 
#include "process.h"
#include <dirent.h>

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

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
	
	char bufCopy[MAX_MSG_LENGTH];
	char buf[MAX_MSG_LENGTH];
	char buf1[MAX_MSG_LENGTH];
	char buf2[MAX_MSG_LENGTH];
    char count;
    int arg;


    socklen_t clieLen = sizeof(clientAddr);
	connfd = Accept(server, (struct sockaddr *) &clientAddr, &clieLen);
    
    recv(cli->sockfd,count,1,0);

    arg = (int) count;
    //dup2(connfd,1);
    
    while(flag == 0)
    {
		clients *cli = (clients *)malloc(sizeof(clients));
		cli->addres = clientAddr;
		cli->sockfd = connfd;
        comArg *comar = (comArg *)malloc(sizeof (comArg)); 
        
        switch(arg)
        {
            case '1':
            {
                recv(cli->sockfd, comar->buf, MAX_MSG_LENGTH,0);
                Pthread_create(&tid, NULL, &handleClient, (void *)cli, (void*)comar);
                break;
            }
                
            case '2':
            {
                recv(cli->sockfd,comar->buf, 3, 0);
                recv(cli->sockfd,comar->buf1, MAX_MSG_LENGTH,0);
                Pthread_create(&tid, NULL, &handleClient, (void *)cli, (void*)comar);
                break;
            }
            
            case '3':
            {
                recv(cli->sockfd,comar->buf, 3, 0);
                recv(cli->sockfd,comar->buf1, MAX_MSG_LENGTH,0);
                recv(cli->sockfd,comar->buf2, MAX_MSG_LENGTH,0);
                Pthread_create(&tid, NULL, &handleClient, (void *)cli, (void*)comar);
                break;
            }

            case '4':
            {
                recv(cli->sockfd,comar->buf, 3, 0);
                recv(cli->sockfd,comar->buf1, MAX_MSG_LENGTH,0);
                recv(cli->sockfd,comar->buf3, 3,0);
                recv(cli->sockfd,comar->buf2, MAX_MSG_LENGTH,0);
                Pthread_create(&tid, NULL, &handleClient, (void *)cli, (void*)comar);
                break;
            }
            default:
            {
                perror("Error\n");
                flag = 1;
            }
                
        }
		//Pthread_create(&tid, NULL, &handleClient, (void *)cli);
    }
    
    close(cli->sockfd);
    free(cli);
    bzero(buf, 3);
    bzero(buf1, MAX_MSG_LENGTH);
    bzero(buf2, MAX_MSG_LENGTH);
    close(server);
    return 0;
}