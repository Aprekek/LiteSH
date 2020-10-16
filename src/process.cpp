#include "process.h"

int launchLab2() {
    const char *path = "./filesystem/project";
    char *str;
    str = (char*)malloc(sizeof(char) * 256);
    int status;
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        cout << "Enter argument: ";
        cin >> str;
        execl(path, path, str, NULL);
        _exit (EXIT_FAILURE);
    } else if (pid < 0)
        status = -1;
    else if (waitpid (pid, &status, 0) != pid)
        status = -1;

    return status;
}

int spawnProcess() {
    int status = 0;
    char *path;
    path = (char*)malloc(sizeof(char) * 256);
    cout << "Enter name process or path to process: ";
    cin >> path;

    pid_t pid;
    pid = fork();

    if (pid == 0) {
        execl(path, path, NULL);
    } else if (pid < 0)
        status = -1;
    else if (waitpid(pid, &status, 0) != pid)
        status = -1;

    return status;
}

int spawnProcessFone() {
    int status = 0;
    char *path;
    path = (char*)malloc(sizeof(char) * 256);
    cout << "Enter name process or path to process: ";
    cin >> path;

    pid_t pid;
    pid = fork();

    if (pid == 0) {
        execl(path, path, NULL);
        _exit (EXIT_FAILURE);
    } else if (pid < 0)
        status = -1;
    else if (waitpid(pid, &status, WNOHANG) != 0)
        status = -1;

    return status;
}



void signal_handler(int signal_num) 
{ 
    cout << "The interrupt signal is (" << signal_num << "). \n"; 
} 
  
void catchSignal() 
{
    int a, i = 0;
    signal(SIGABRT, signal_handler);   
    // register signal SIGABRT and signal handler   
    cout << "How many signal you want gives?\n";
    cin >> a; 
    while(i!=a)
    { 
        cout << "Signal Handled" << endl;
        i++;
    }
}
