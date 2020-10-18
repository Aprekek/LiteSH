#include <iostream>
#include "fileheader.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    string str, strHelp, strH, strLab2, strProc, strProcBg, strSignal;
    strHelp = "--help";
    strH = "-h";
    strLab2 = "-l2";
    strProc = "-p";
    strProcBg = "-pb";
    strSignal = "-signal";

    if (argc == 2) {
        if (argv[1] == strHelp || argv[1] == strH) // Help
            Help();
        else if (argv[1] == strLab2) {
            if (launchLab2() != 0)
                cout << "Error" << endl;
        } else if (argv[1] == strProc) {
            if (spawnProcess() != 0)
                cout << "Error" << endl;
        } else if (argv[1] == strProcBg) {
            if (spawnProcessFone() != 0)
                cout << "Error" << endl;
        } else if (argv[1] == strSignal) {
            catchSignal();   
        } else {
            cout << "Incorrect argument" << endl;
            return 0;
        }
    } else {
        cout << "Incorrect argument" << endl;
        return 0;
    }

    return 0;
}