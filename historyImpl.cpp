#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#include<string>
#include<sstream>
#include "operations.h"
using namespace std;




void getHistory() {
	string lines = readEnvFile("HISTSIZE=");
	stringstream S_lines(lines);
	int line = 0;
	S_lines >> line;
	string historyFile=".r_history";
    const char *historyFP = historyFile.c_str();
    FILE* FP;
    FP = fopen(historyFP, "r");
    if (FP == NULL) {
        cout << "Error opening the history file" << endl;
    }
    int count = 0;
    unsigned long long pos;
    char str[200];

    if (fseek(FP, 0, SEEK_END)) {
        perror("fseek error");
    } else {
        pos = ftell(FP);
        while(pos) {
            if (!fseek(FP, --pos, SEEK_SET)) {
                if (fgetc(FP) == '\n') {
                    fgets(str, sizeof(str), FP);
                    cout << str;
                    if (count++ == line) {
                    	break;

                    }
                  }
            } else {
                perror("fseek error");
            }
        }

        if (count < line) {
            fseek(FP, 0, SEEK_SET);
            fgets(str, sizeof(str), FP);
            cout << str;
        }
    }


}
