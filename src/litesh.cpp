#include "fileheader.hpp"

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
        _exit (EXIT_FAILURE);
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



void signal_handler(int sig) { 
    printf("\nSignal %i - %s\n", sig, sys_siglist[sig]);
    if (sig == 1) {
        exit(EXIT_SUCCESS);
    } else if (sig == 20) {
        string str;
        string str2 = "exit";
        cout << "Enter 'exit'" << endl;
        cin >> str;
        if (str == str2)
            exit(EXIT_SUCCESS);
        else
            cout << "Error" << endl;
    }
} 
  
void catchSignal() {
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
