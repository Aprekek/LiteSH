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
            cout << "1 - Command line from lab 2" << endl;
            cout << "2 - Spawn a process by name" << endl;
            cout << "3 - Put the process in the background" << endl;
            cout << "4 - Processing of signals" << endl;
            cout << "===========================" << endl;
            cin >> str;
            if (str == "1") {
                if (launchLab2() != 0)
                    cout << "Error" << endl;
            } else if (str == "2") {
                if (spawnProcess() != 0)
                    cout << "Error" << endl;
            } else if (str == "3") {
                if (spawnProcessFone() != 0)
                    cout << "Error" << endl;
            } else if (str == "4") {

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