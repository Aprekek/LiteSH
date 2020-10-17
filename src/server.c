#include "Clieserv.h" 
#include "process.h"

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

    Bind(server, (struct sockaddr *) &serverAdr, sizeof serverAdr);

    Listen(server, 5);

    socklen_t clieLen = sizeof(clientAddr);
    connfd = Accept(server, (struct sockaddr *) &clientAddr, &clieLen);

    char buf[1024];
		
    socklen_t clieLen = sizeof(clientAddr);
    connfd = Accept(server, (struct sockaddr *) &clientAddr, &clieLen);
		  
    dup2(connfd,1);    //redirect stdout
     while(1)
     {
	recv(connfd,buf, MAX_MSG_LENGTH,0);
	/*If the message recieved was END_STRING, exit this loop*/
	system(buf);	
	bzero(buf, MAX_MSG_LENGTH);
     }	
    
    close(connfd);
    sleep(1);
    close(server);
    return 0;
}
