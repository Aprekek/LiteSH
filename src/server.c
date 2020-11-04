#include "Clieserv.h"
#include "filesystem.h" 
#include "process.h"

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[])
{
    if (argc < 3)
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

    Bind(server, (struct sockaddr *) &serverAdr, sizeof serverAdr);

    Listen(server, 3);
	
    while(connfd = accept(server, NULL, (socklen_t *)&clieLen))
    {
		socklen_t clieLen = sizeof(sockaddr_in);
        pthread_t tid;
		clients *cli = (clients *)malloc(sizeof(clients));
		
		cli->sockfd = connfd;
        cli->argProgram = argv[2];

		Pthread_create(&tid, NULL, handleClient, (void *)cli);
        pthread_detach(tid);
    }	
    
    return 0;
}
