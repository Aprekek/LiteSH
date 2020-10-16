#include <iostream>
#include "fileheader.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    char* file; 
    char* dir;
    file = (char*)malloc(sizeof(char) * 256);
    dir = (char*)malloc(sizeof(char) * 256);
    string str, strFile, strPath;
    string strHelp, strH, strMoving, strCopy, strDelete, strSize, strAllFiles, strAllProc;
    strHelp = "--help";
    strH = "-h";
    strMoving = "-m";
    strCopy = "-c";
    strDelete = "-d";
    strSize = "-s";
    strAllFiles = "-af";
    strAllProc = "-ap";

    if (argc == 2) {
        if (argv[1] == strHelp || argv[1] == strH) { // Help
            Help();

        } else if (argv[1] == strMoving) { // Перемещение файла;
            cout << "Enter file name or path to file: ";
            cin >> strFile;
            cout << "Enter path to dir moving: ";
            cin >> strPath;
            moveFile(strPath, strFile);
            
        } else if (argv[1] == strCopy) { // Копирование файла;
            cout << "Enter file name or path to file: ";
            cin >> strFile;
            cout << "Enter path to dir copy: ";
            cin >> strPath;
            copyFile(strPath, strFile);

        } else if (argv[1] == strDelete) { // Удаление файла;
            cout << "Enter file name or path to file: ";
            cin >> strFile;
            deleteFile(strFile);

        } else if (argv[1] == strSize) { // Подсчет общего размера указанной директории или файла;
            cout << "File or Dir" << endl;
            cout << "If file - enter 'f'" << endl;
            cout << "If dir - enter 'd'" << endl;
            cin >> str;

            if (str == "f") {
                cout << "Enter file name or path to file: ";
                cin >> file;
                cout << getFileSize(file) << " Byte" << endl;
            } else if (str == "d") {
                cout << "Enter path to the dir: ";
                cin >> dir;
                cout << getDirSize(dir) << " Byte" << endl;
            } else {
                cout << "Incorrect arguments" << endl;
            }

        } else if (argv[1] == strAllFiles) { // Отображение всех файлов в указанной директории;
            cout << "Enter path to the dir: ";
            cin >> dir;
            displayAllFiles(dir);

        } else if (argv[1] == strAllProc) { // Отображение всех процессов из файловой системы procfs.
            displayProc();
        }
    } else {
        cout << "Incorrect arguments" << endl;
        cout << "Enter ./project --help | -h" << endl;
    }

    return 0;
}