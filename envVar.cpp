#include<string>
#include<iostream>
#include<fstream>
using namespace std;
#include "operations.h"

// calling fun to read all content of env variable file rrf
string readEnvFile(string promptString){
	string eachLine;
	ifstream envFile;
	envFile.open(".rrc");
	if(envFile.is_open()){
		while(getline(envFile,eachLine)){
			if(eachLine.find(promptString) != string::npos){
				size_t lineFirstPlace = eachLine.find(promptString);
				eachLine.erase(lineFirstPlace, promptString.length());
				return eachLine;
			}
		}
		envFile.close();
	}
	return 0;
}


//below function is used to keep the command record tracking in .r_history of HOME
void historyRecord(string inputCommand){
	ofstream histFile;
	histFile.open(".r_history",ios::in|ios::out|ios::app);
	histFile << inputCommand <<endl;
	histFile.close();
	}
