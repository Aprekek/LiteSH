#include "Clieserv.h"
#include "filesystem.h"
#include "process.h"

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        perror("ERROR, no port provided\n");
        exit(1);
    }
    
    int read_size = 0;
    char buf[256];
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


    printf("Please read \n");

    printf ("►копирование файла(3 arg);
    \n*введите путь к файлу и место, куда хотите переместить
    \n►перемещение файла(3 arg);
    \n*введите путь к файлу и место, куда хотите переместить
    \n►удаление файла(2 arg); 
    \n*введите путь к удаляемому файлу
    \n►определение размера файла(2 arg);
    \n*введите путь к файлу
    \n►определение размера директории(2 arg);
    \n*укажите путь до заданной дирректории\n");

    printf ("►отображение всех процессов вашей ОС(1 arg);
    \n►создание процесса по его имени(2 arg);
    \n*укажите имя или путь до процесса
    \n►создание процесса для запуска программы работы с файлами(2 arg);
    \n*укажите путь, где запустить процесс
    \n►перевод заданного процесса в фоновый режим(2 arg);
    \n*укажите имя или путь до процесса
    \n►отображение сигналов вашей ОС(1 arg).\n")


    int a = 0, i = 0;
    while (a == 0)
    {
        printf("Enter counts parametrs\n");
        scanf("%d ", a);

    }
    char b = a;
    send(sockfd,b,1,0);

	while(i < a)
	{
        fgets(buf,MAX_MSG_LENGTH,stdin);
		send(sockfd,buf,MAX_MSG_LENGTH,0);
        i++;
		bzero(buf, MAX_MSG_LENGTH);
	}
		
	
	return 0;
}