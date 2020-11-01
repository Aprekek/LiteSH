#include "Clieserv.h"


int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        perror("ERROR, no port provided\n");
        exit(1);
    }
    
    int read_size = 0;
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

    /*
    printf("\n Please read");
    printf ("\n ►копирование файла(3 arg);");
    printf("\n *введите путь к файлу и место, куда хотите переместить");
    printf("\n ►перемещение файла(3 arg);");
    printf("\n *введите путь к файлу и место, куда хотите переместить");
    printf("\n ►удаление файла(2 arg); ");
    printf("\n *введите путь к удаляемому файлу");
    printf("\n ►определение размера файла(2 arg);");
    printf("\n *введите путь к файлу");
    printf("\n ►определение размера директории(2 arg);");
    printf("\n *укажите путь до заданной дирректории\n");

    printf (►отображение всех процессов вашей ОС(1 arg);
    \n ►создание процесса по его имени(2 arg);
    \n *укажите имя или путь до процесса
    \n ►создание процесса для запуска программы работы с файлами(2 arg);
    \n *укажите путь, где запустить процесс
    \n ►перевод заданного процесса в фоновый режим(2 arg);
    \n *укажите имя или путь до процесса
    \n ►отображение сигналов вашей ОС(1 arg).\n)*/

    char buf[1024];
    int i;
    
    while(1)
    {
    
        int nreads = read(sockfd, buf, 256);
        if (nreads!=-1)
            write (STDOUT_FILENO, buf, strlen(buf));
    }
    

    /*
    int shutdown(int s, int how);

    Первый аргумент функции - сокет-дескриптор, который должен быть закрыт. Второй аргумент - целое значение, указывающее, каким образом закрывается сокет, а именно:

    0 - сокет закрывается для чтения;
    1 - сокет закрывается для записи;
    2 - сокет закрывается для чтения и для записи.
    */
	
	return 0;
}
