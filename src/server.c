#include "Clieserv.h"
#include "filesystem.h" 


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
    //listenfd = serverAdr
    struct sockaddr_in serverAdr = {0};
    struct sockaddr_in clientAddr = {0};
    
    int server = Socket(AF_INET, SOCK_STREAM, 0); //протокол
    serverAdr.sin_family = AF_INET;
    serverAdr.sin_addr.s_addr = inet_addr(ip);
    serverAdr.sin_port = htons(port);
    socklen_t clieLen = sizeof(sockaddr_in);
    
    Bind(server, (struct sockaddr *) &serverAdr, sizeof serverAdr);

    Listen(server, 3);
	
    while(connfd = accept(server, NULL, (socklen_t *)&clieLen))
    {
        pthread_t tid;
		clients *cli = (clients *)malloc(sizeof(clients));
		
		cli->sockfd = connfd;
		printf("1\n");
		Pthread_create(&tid, NULL, handleClient, (void *)cli);
        pthread_detach(tid);
    }	
    
    return 0;
}
