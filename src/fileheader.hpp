#ifndef H_FILE
#define H_FILE

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string>
#include <sys/stat.h>
#include <cstdlib>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

// Help function
void showMenu();
void printArguments();
void printReadme();
void Help();

int launchLab2();
int spawnProcess();
void signal_handler( int signal_num );
void catchSignal (); 

#endif
