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
#include <ftw.h>
#include <fcntl.h> /* Определение констант O_* */
#include <unistd.h>

using namespace std;

// Copy file
void copyFile(string path, string fileName);

// Move file
void moveFile(string path, string fileName);

// Delete file
void deleteFile(string fileName);

// All process
int IsNumeric(const char* ccharptr_CharacterList);
int displayProc(char *pathFile);

// Display all files
static int dirTree(const char *pathname, const struct stat *sbuf, int type, struct FTW *ftwb); 
void displayAllFiles(const char *dirName, char *pathFile);


// Size file or dir
void printGetDirSize(const char *dirName, char *pathFile);
void getFileSize(const char * fileName, char *pathFile);
#endif
