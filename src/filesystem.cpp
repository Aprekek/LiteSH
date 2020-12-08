#include "filesystem.h"

#define _GNU_SOURCE
#define PROC_DIRECTORY "/proc/"
#include <string.h>
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
        cout << "File or dir opening error" << endl;

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
    dirent *pdir;
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
        else {
            //fcout(stdout, "   %ld: - Filename : %s\n",st.st_size, pdir->d_name); //доп. проверка файлов
            Size += st.st_size;
        }
    }
    return Size;
}


void printArguments()
{
    cout << "-h"<<endl;
    cout << "-help"<< endl;
    cout << "-m - Move files"<<endl;
    cout << "-c - Copying file"<<endl;
    cout << "-d - File deletion"<<endl;
    cout << "-s - Calculating the total size of the specified directory or file"<<endl;
    cout << "-f - Displaying all files in the specified directory"<<endl;
    cout << "-p - Displaying all processes from the procfs file system"<<endl;

    cout << "\n Please read";
    cout <<"\n ►копирование файла(3 arg);";
    cout <<"\n *введите путь к файлу и место, куда хотите переместить";
    cout <<"\n ►перемещение файла(3 arg);";
    cout <<"\n *введите путь к файлу и место, куда хотите переместить";
    cout <<"\n ►удаление файла(2 arg); ";
    cout <<"\n *введите путь к удаляемому файлу";
    cout <<"\n ►определение размера файла(2 arg);";
    cout <<"\n *введите путь к файлу";
    cout << "\n ►определение размера директории(2 arg);";
    cout << "\n *укажите путь до заданной дирректории\n";
}

void printReadme()
{
    cout << "This program performs the following functions:"<<endl<<
         "*copying a file;"<<endl<<
         "*moving a file;" <<endl<<
         "*deleting a file;"<<endl<<
         "*calculating the total size of a directory or file; "<<endl<<
         "*displaying all file system processes;" <<endl<<
         "*displaying all files in a directory."<<endl<<
         "Check the appropriate arguments before starting!"<<endl<<
         "*calling a line for entering project call commands;"<<endl<<
         "*a product of the process by its name;" <<endl<<
         "*return to the command line;"<<endl<<
         "*putting the process in the background mode; "<<endl<<
         "*receive and process signals from external programs and the operating system;" <<endl<<
         "Check the appropriate arguments before starting!"<<endl;
}

void Help()
{
    printReadme();
    printArguments();
    cout << "By: Пинов Даниил Игоревич \n Есикова Анастасия Дмитриевна \n Лепёхин Даниил Александрович"<< endl;
}

void startProg(int argc, char* argv[])
{
    char* file;
    char* dir;

    file = (char*)malloc(sizeof(char) * 256);
    dir = (char*)malloc(sizeof(char) * 256);
    string str, strFile, strPath;
    string strHelp, strH, strMoving, strCopy, strDelete, strSize, strAllFiles, strAllProc;
    strHelp = "-help";
    strH = "-h";
    strMoving = "-m";
    strCopy = "-c";
    strDelete = "-d";
    strSize = "-s";
    strAllFiles = "-f";
    strAllProc = "-p";

    if (argv[1] == strHelp || argv[1] == strH) {
        Help();
    } else if (argv[1] == strMoving) { // Перемещение файла;
        strPath = argv[2];
        strFile = argv[3];
        moveFile(strPath, strFile);

    } else if (argv[1] == strCopy) {   
        strPath = argv[2];
        strFile = argv[3];
        copyFile(strPath, strFile);

    } else if (argv[1] == strDelete) {   // Удаление файла;
        strFile = argv[3];
        deleteFile(strFile);

    } else if (argv[1] == strSize) {   // Подсчет общего размера указанной директории или файла;
        str = argv[2];
        if (str == "f") {
            file = argv[3];
            cout << getFileSize(file) << " Byte" << endl;
        } else if (str == "d") {
            dir =  argv[3];
            cout << getDirSize(dir) << " Byte" << endl;
        } else {
            cout << "Incorrect arguments" << endl;
        }

    } else if (argv[1] == strAllFiles) {   // Отображение всех файлов в указанной директории;
        dir = argv[2];
        displayAllFiles(dir);

    } else if (argv[1] == strAllProc) {   // Отображение всех процессов из файловой системы procfs.
        displayProc();
    }

}
