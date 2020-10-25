#include "Clieserv.h"
#include "filesystem.h"
#include "process.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("ERROR, no port provided\n");
        exit(1);
    }

    char command[64];
    int length;
	char *ip = "127.0.0.1";
	int port = atoi(argv[1]);
    struct sockaddr_in server = {0};

    int sockfd = Socket(AF_INET, SOCK_STREAM, 0); //протокол
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(port);

    // Connect to Server
    Connect(sockfd, (struct sockaddr *)&server, sizeof server); 

	printf("\n**********Welcome**********\n");
    
    int read_size;
    char buf[256];
	
	while(fgets(buf,MAX_MSG_LENGTH,stdin))
	{
		send(sockfd,buf,MAX_MSG_LENGTH,0);
		
		while(1)
		{
		    read_size = read(sockfd,buf,MAX_MSG_LENGTH);
		    //Print read_size characters from buf
		    printf("%.*s\n", read_size, buf);
		    if (read_size < MAX_MSG_LENGTH)
		        //Keep on reading until read_size < MAX_MSG_LENGTH, then exit this loop
		        break;
		    
		}
		
	bzero(buf, MAX_MSG_LENGTH);
	}	
	
	return 0;
}
