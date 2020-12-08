#ifndef H_FILESYSTEM
#define H_FILESYSTEM

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string>
#include <sys/stat.h>
#include <cstdlib>
#include <fstream>
#include <sys/types.h> // for opendir(), readdir(), closedir()
#include <sys/stat.h> // for stat()

using namespace std;

// Copy file
int copyFile(string path, string fileName);

// Move file
int moveFile(string path, string fileName);

// Delete file
int deleteFile(string fileName);

// All process
int IsNumeric(const char* ccharptr_CharacterList);
int displayProc();

// Display all files
int displayAllFiles(const char *dirName);

void Help();
void printReadme();
void printArguments();

void startProg(int argc, char* argv[]); 

// Size file or dir
int getFileSize(const char *fileName);
int getDirSize(const char *dirName);

#endif
