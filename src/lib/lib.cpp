#include "lib.h"

// Size dir or file
int getFileSize(const char * fileName) //вывод размера файла в текущей директории
{
    struct stat file_stat;
    stat(fileName, &file_stat);
    return file_stat.st_size;
}

int getDirSize(const char *dirName)
{
    DIR *dir;
    struct dirent *pdir;
    struct stat st;
    long Size = 0;
    char *tmpstr; //буфер пути
    dir = opendir(dirName);
	if(dir == NULL)
	{
	    perror("Something happened trying to open directory");
	    exit(1);
	}
	while((pdir = readdir(dir)) != NULL) 
	{
		if(pdir->d_name[0] == '.') continue;
		asprintf(&tmpstr, "%s/%s", dirName, pdir->d_name);//выводит и сразу же записывает в памяти директорию, в которую заходит, с указанием её пути
		if(lstat(tmpstr, &st) != 0)//ошибка про чтении файла
		{
		    perror("Something happened with file.");
		    exit(1);
		};
		if(S_ISDIR(st.st_mode)) getDirSize(tmpstr); //проверка на доступность файла
		else{
		    //fprintf(stdout, "   %ld: - Filename : %s\n",st.st_size, pdir->d_name); //доп. проверка файлов
		    Size += st.st_size;
		}
    }
    return Size;
}

#define _GNU_SOURCE
#define PROC_DIRECTORY "/proc/"

using namespace std;

// Copy file
void copyFile(string path, string fileName) {
    int pos;
    string newFileName;
    pos = fileName.rfind("/");

    if (pos != -1) {
        newFileName = fileName.substr(pos + 1);
        path = path + "/" + newFileName;
    } else 
        path = path + "/" + fileName;

    ifstream file (fileName, ios_base::in | ios_base::binary);
    ofstream newFile (path, ios_base::out | ios_base::binary);

    if (file.is_open() && newFile.is_open())
        newFile << file.rdbuf();
    else
        cout << "File or dir opening error" << endl;
    
    file.close();
    newFile.close();
}
// Copy file

// Move file
void moveFile(string path, string fileName) {
    copyFile(path, fileName);
    deleteFile(fileName);
}
// Move file

// Delete file
void deleteFile(string fileName) {
    const char *str = fileName.c_str();

    if (remove(str) != 0)
        cout << "Error delete file" << endl;
}
// Delete file


// All process
int IsNumeric(const char* ccharptr_CharacterList)
{
    for ( ; *ccharptr_CharacterList; ccharptr_CharacterList++)
        if (*ccharptr_CharacterList < '0' || *ccharptr_CharacterList > '9')
            return 0; // false
    return 1; // true
}

int displayProc()
{
    struct dirent* dirEntity = NULL;
    DIR* dir_proc;

    dir_proc = opendir(PROC_DIRECTORY) ;
    if (dir_proc == NULL)
    {
        perror("Couldn't open the " PROC_DIRECTORY " directory") ;
        return (pid_t)-2 ;
    }

    while ((dirEntity = readdir(dir_proc)) != 0) 
    {
        if (dirEntity->d_type == DT_DIR) {
            if (IsNumeric(dirEntity->d_name)) {
                string path = string(PROC_DIRECTORY) + dirEntity->d_name + "/cmdline";

                ifstream cmdLineFile(path.c_str());
                string cmdLine;
                if (cmdLineFile) {
                    getline(cmdLineFile, cmdLine);
                }
                cout << "pid: " << dirEntity->d_name << " " << cmdLine << endl;
            }
        }
    }
    closedir(dir_proc);
}
// All process


// Display all files
void displayAllFiles(const char *dirName)
{
    DIR *dir;
    dirent *pdir;
    dir = opendir(dirName);
    struct stat st;
    char *tmpstr; //буфер пути
	if(pdir == NULL)
	{
	    perror("Something happened trying to open directory");
	    exit(1);
	}
	while((pdir = readdir(dir)) != NULL) 
	{
		if(pdir->d_name[0] == '.') continue;
		asprintf(&tmpstr, "%s/%s", dirName, pdir->d_name);//выводит и сразу же записывает в памяти директорию, в которую заходит, с указанием её пути
		if(lstat(tmpstr, &st) != 0)//ошибка про чтении файла
		{
		    perror("Something happened with file.");
		    exit(1);
		};
		if(S_ISDIR(st.st_mode)) displayAllFiles(tmpstr); //проверка на доступность файла
		else
            cout << "Filename "<< pdir->d_name << endl;	
    }
}
// Display all files
