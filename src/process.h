#ifndef H_FILE
#define H_FILE

#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <cstdlib>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <csignal>

using namespace std;

int launchLab2();
int spawnProcess();
int spawnProcessFone();

void catchSignal();
void signal_handler(int signal_num);

#endif
