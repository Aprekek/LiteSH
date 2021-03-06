#include "Clieserv.h"
#include "filesystem.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        perror("ERROR, no port provided\n");
        exit(1);
    }

    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);
    struct sockaddr_in server = {0};

    int sockfd = Socket(AF_INET, SOCK_STREAM, 0); 
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(port);

    Connect(sockfd, (struct sockaddr *)&server, sizeof server);
    
    while(1) {
        char *sendBuf = (char *) calloc(SizeBufSend, sizeof (char));
        char *recvBuf = (char *) calloc (SizeBufRecv, sizeof (char));
        printf("\n**********Welcome**********\n");
        printf("Enter operation and param\n");

        fgets(sendBuf, SizeBufSend, stdin);

        if (strcmp(sendBuf, "exit") == 0)
            return 0;

        if (write (sockfd, sendBuf, strlen(sendBuf)) < 1) {
            perror ("ERROR, message can't sended");
            break;
        }

        if (read(sockfd, recvBuf,SizeBufRecv) == -1) {
            perror ("ERROR, message can't recieved");
            break;
        } else
            puts(recvBuf);

        free(sendBuf);
        free(recvBuf);
    }

    close(sockfd);
    return 0;
}
