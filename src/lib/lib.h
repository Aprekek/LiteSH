#ifndef LIB_H
#define LIB_H

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
void copyFile(string path, string fileName);

// Move file
void moveFile(string path, string fileName);

// Delete file
void deleteFile(string fileName);

// All process
int IsNumeric(const char* ccharptr_CharacterList);
int displayProc();

// Display all files
void displayAllFiles(const char *dirName);

int getFileSize(const char * fileName);
int getDirSize(const char *dirName);

#endif