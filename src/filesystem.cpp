#include "filesystem.h"
#include <string.h>

#define PROC_DIRECTORY "/proc/"


using namespace std;

// Copy file
void copyFile(string path, string fileName) 
{
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
    {
        exit (EXIT_FAILURE);
        cout << "File or dir opening error" << endl;
    }
    file.close();
    newFile.close();
}
// Copy file

// Move file
void moveFile(string path, string fileName) 
{
    copyFile(path, fileName);
    deleteFile(fileName);
}
// Move file

// Delete file
void deleteFile(string fileName) 
{
    const char *str = fileName.c_str();

    if (remove(str) != 0)
    {
        exit (EXIT_FAILURE);
        cout<< "Error delete file" << endl;
    }
        
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

int displayProc(char *pathFile)
{
    ofstream fout(pathFile);
    struct dirent* dirEntity = NULL;
    DIR* dir_proc;

    dir_proc = opendir(PROC_DIRECTORY) ;
    if (dir_proc == NULL)
    {
        fout << "Couldn't open the " PROC_DIRECTORY " directory" << endl;
        fout.close();
        return 0;
    }

    while ((dirEntity = readdir(dir_proc)) != 0) 
    {
        if (dirEntity->d_type == DT_DIR) 
        {
            if (IsNumeric(dirEntity->d_name)) 
            {
                string path = string(PROC_DIRECTORY) + dirEntity->d_name + "/cmdline";

                ifstream cmdLineFile(path.c_str());
                string cmdLine;
                if (cmdLineFile) {
                    getline(cmdLineFile, cmdLine);
                }
                fout << "pid: " << dirEntity->d_name << cmdLine << endl;
            }
        }
    }
    closedir(dir_proc);
    fout.close();
}
// All process
static int dirTree(const char *pathname, const struct stat *sbuf, int type, struct FTW *ftwb) 
{
	printf("%s\n", &pathname[ftwb->base]);
	return 0;
}

// Display all files
void displayAllFiles(const char *dirName, char *pathFile)
{
    struct dirent *dp;
	DIR *dirp = opendir(dirName);
	for (;;) 
	{
		dp = readdir(dirp);
		if (dp == NULL)
			break;
		if (!(strcmp(dirName, ".") == 0))
			continue;		
	}
	int flags = FTW_DEPTH;

	int fp = open(pathFile, O_WRONLY | O_APPEND);
	dup2(fp, 1);
    nftw(dirName, dirTree, 10, flags);
}
// Display all files


// Size dir or file
void getFileSize(const char * fileName, char *pathFile) //вывод размера файла в текущей директории
{
    ofstream fout(pathFile);
    struct stat file_stat;
    stat(fileName, &file_stat);
    fout << file_stat.st_size << endl;
    fout.close();

}

int getDirSize(const char *dirName)
{
    DIR *dir;
    dirent *pdir;
    struct stat st;
    long Size = 0;
    char *tmpstr; //буфер пути
    dir = opendir(dirName);
	if(dir == NULL)
	{
        exit (EXIT_FAILURE);
	    perror("Something happened trying to open directory");
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

void printGetDirSize(const char *dirName, char *pathFile)
{
    ofstream fout(pathFile);
    double Size = getDirSize(dirName);
    fout << Size << endl;
    fout.close();
}