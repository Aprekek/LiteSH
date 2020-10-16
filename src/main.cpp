#include <iostream>
#include "fileheader.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    string str, strHelp, strH;
    strHelp = "--help";
    strH = "-h";

    if (argc == 2) {
        if (argv[1] == strHelp || argv[1] == strH) // Help
            Help();
        else {
            cout << "Incorrect argument" << endl;
            return 0;
        }
    } else if (argc == 1) {
        while (1) {
            cout << "===========================" << endl;
            cout << "Enter the required action: " << endl;
            cout << "'-l2' - Command line from lab 2" << endl;
            cout << "'-p' - Spawn a process by name" << endl;
            cout << "'-pb' - Put the process in the background" << endl;
            cout << "'-signal' - Processing of signals" << endl;
            cout << "===========================" << endl;
            cin >> str;
            if (str == "-l2") {
                if (launchLab2() != 0)
                    cout << "Error" << endl;
            } else if (str == "-p") {
                if (spawnProcess() != 0)
                    cout << "Error" << endl;
            } else if (str == "-pb") {
                if (spawnProcessFone() != 0)
                    cout << "Error" << endl;
            } else if (str == "-signal") {
                catchSignal();    
            } else {
                cout << "Incorrect argument" << endl;
            }
        }
    } else {
        cout << "Incorrect argument" << endl;
        return 0;
    }

    return 0;
}