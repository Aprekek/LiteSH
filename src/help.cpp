#include "fileheader.hpp"

using namespace std;

void showMenu() 
{
  cout << "=========================="<< endl;
	cout << "Select:"<<endl;
	cout << "the program belongs A"<<endl;
	cout << "available arguments ar"<<endl;
	cout << "about the program r"<<endl;
	cout << "example e"<<endl;
  cout << "=========================="<< endl;
}
   
void printArguments()
{
  cout << "--help"<<endl;
	cout << "-h"<<endl;
  cout << "-m - Move files"<<endl;
	cout << "-c - Copying file"<<endl;
	cout << "-d - File deletion"<<endl;
	cout << "-s - Calculating the total size of the specified directory or file"<<endl;
	cout << "-af - Displaying all files in the specified directory"<<endl;
	cout << "-ap - Displaying all processes from the procfs file system"<<endl;
	cout << "-l2 - Calling a line for entering project call commands"<<endl;
	cout << "-p - A product of the process by its name"<<endl;
	cout << "-pb - Putting the process in the background mode"<<endl;
	cout << "-signal - Signals from external progmans or OS"<<endl;
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
    "Check the appropriate arguments before starting!"<<endl; 
    "*calling a line for entering project call commands;"<<endl<<  
    "*a product of the process by its name;" <<endl<<  
    "*return to the command line;"<<endl<<
    "*putting the process in the background mode; "<<endl<<
    "*receive and process signals from external programs and the operating system;" <<endl<<
    "Check the appropriate arguments before starting!"<<endl;
}

void Help()
{
    char command;
    do {
        showMenu();
        cin>>command;
        switch(command)
        {
            case 'A' : cout << " Пинов Даниил Игоревич \n Есикова Анастасия Дмитриевна \n Лепёхин Даниил Александрович"<< endl; 
                            break;
            case 'ar' : printArguments();
                            break;
            case 'r' : printReadme();
                            break;
            case 'e' : cout << "example"<<endl;
                            break;   
            default : cout<<"INVALID CHOICE \n";
         }
        cout<<"Continue? (y/n) ";
        cin>>command;
    } while(command == 'y' || command == 'Y');
}
