#include "Clieserv.h"


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
    


    socklen_t clieLen = sizeof(clientAddr);
	connfd = Accept(server, (struct sockaddr *) &clientAddr, &clieLen);
    //dup2(connfd,1);
    
    while(flag == 0)
    {
		clients *cli = (clients *)malloc(sizeof(clients));
		cli->addres = clientAddr;
		cli->sockfd = connfd; 
        flag = 1;
        Pthread_create(&tid, NULL, &handleClient, (void *)cli);
        
		//Pthread_create(&tid, NULL, &handleClient, (void *)cli);
    }
    
    close(connfd);
    close(server);
    return 0;
}