#include<iostream>
#include<string>
#include <stdlib.h>
using namespace std;
#include "operations.h"



void setPromptString(){
	string hostVar = readEnvFile("HOSTNAME=");
	string userVar = readEnvFile("USER=");
	cout <<hostVar<<"@"<<userVar<<"$ ";
	inputArgs();
}


void inputArgs(){
	string initialCommand;
	const string exitStr= "exit";
	//cin >> initialCommand; I cannot use the cin because it is not taking spaces from input
	getline(cin,initialCommand);
	historyRecord(initialCommand);
	if(initialCommand.compare(exitStr) == 0){
		exit(0);
	}
	else{
		//below code check for the given command in /bin and /usr/bin dir and calls methods in commandoperations.cpp
		string path1 = "/bin/";
		string fullPath=path1+initialCommand;
		if(checkCommandExist(fullPath) == 1){
			//cout << checkCommandExist(fullPath)<<endl;
			cmdExecFuntion(fullPath);
			//need to above line and write a program to execute cmdExecution.cpp
			setPromptString();
		}
		else{
			string path2="/usr/bin/";
			string fullPath1=path2+initialCommand;
			if(checkCommandExist(fullPath1) == 1){
				//cout << checkCommandExist(fullPath1)<<endl;
				cmdExecFuntion(fullPath1);
				setPromptString();
			}
			else{
				cout << "command not exist"<<endl;
				setPromptString();
			}
		}
	}
}

