#include "process.h"
#include <fcntl.h>              /* Определение констант O_* */
#include <unistd.h>

int launchLab2(char *pathFile) 
{
    const char *path = "./filesystem/project";
    string str;
    str = (char*)malloc(sizeof(char) * 32);
    int status;
    pid_t pid;
    pid = fork();
    

    if (pid == 0) 
    {
        execl(path, path, NULL);
        _exit (EXIT_FAILURE);
    
    } else if (pid < 0) {
        status = -1;
    }
    else if (waitpid (pid, &status, 0) != pid) 
        status = -1;
    
    return status;
}

int spawnProcess(char *path, char *pathFile) 
{
    int status = 0;
    pid_t pid;
    pid = fork();

    if (pid == 0) 
    {
        execl(path, path, NULL);
    } else if (pid < 0)
        status = -1;
    else if (waitpid(pid, &status, 0) != pid)
        status = -1;

    return status;
}

int spawnProcessFone(char *path) 
{
    int status = 0;
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



void signal_handler(int sig) 
{ 
    printf("\nSignal %i - %s\n", sig, sys_siglist[sig]);
    if (sig == 1) 
    {
        exit(EXIT_SUCCESS);
    } else if (sig == 20) 
    {
        string str;
        exit(EXIT_SUCCESS);
    }
} 
  
void catchSignal() 
{
    int sig;
    struct sigaction sa;
    sigset_t set;
    sigfillset(&set);
    sa.sa_handler = signal_handler;
    sigaction(SIGHUP, &sa, 0);
    sigaction(SIGTSTP, &sa, 0);
    sigdelset(&set, SIGHUP);
    sigdelset(&set, SIGTSTP);
    sigprocmask(SIG_SETMASK, &set, 0);
    printf("My pid is %i\n", getpid());

    while(!sigwait(&set, &sig)) 
        printf("\nSignal %i - %s\n", sig, sys_siglist[sig]);

}
