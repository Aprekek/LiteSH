#include "Clieserv.h"
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
    
    while (1) {
        printf("Enter command:\n");
        scanf("%s", command);
        length = strlen(command);

        if (strcmp(command, "exit") == 0) {
            close(sockfd);
            return 0;
        } else {
            write(sockfd, command, length);
        }   
    }
	
	return 0;
}
