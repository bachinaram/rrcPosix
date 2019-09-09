#include<iostream>
#include<cstring>
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
	const string historyStr= "history";
	const string settingStr= "export ";
	const string setter="=";
	string eachLine;
	//cin >> initialCommand; I cannot use the cin because it is not taking spaces from input
	getline(cin,initialCommand);
	historyRecord(initialCommand);
	if(initialCommand.compare(exitStr) == 0){
		exit(0);
	}
	else if(initialCommand.compare(historyStr) == 0){
		getHistory();
		setPromptString();
	}
	else if(initialCommand.find(settingStr) != string::npos){
		string setCommand =  removeExport(initialCommand,settingStr);
		string wholeCommand=setCommand;

		size_t lineSecondPlace= setCommand.find(setter);
		setCommand.erase(lineSecondPlace, setCommand.length()+1);
		//cout << setCommand;
		string setVariable = setCommand+setter;
		string searchString = setVariable;

		int searchResult = searchStr(searchString);
		//cout << searchResult<<endl;
		if(searchResult == 0){
			//cout << setVariable;
			string oldString = readEnvFile(setVariable);
			size_t lineThirdTime= wholeCommand.find(setter);
			//cout << lineThirdTime;
			//cout << wholeCommand.length();
			wholeCommand.erase(0, lineThirdTime+1);
			string newString =wholeCommand;
			int retint = updateOldVariable(oldString,newString);
			//cout << retint <<endl;

		}
		else{
			//cout<<wholeCommand<<endl;
			addNewVariable(wholeCommand);


		}
		setPromptString();
	}
	else{
		//below code check for the given command in /bin and /usr/bin dir and calls methods in commandoperations.cpp
		string path1 = "/bin/";
		string fullPath=path1+initialCommand;
		if(checkCommandExist(fullPath) == 1){
			//cout<<fullPath;
			cmdExecFuntion(fullPath);
			//need to above line and write a program to execute cmdExecution.cpp
			setPromptString();
		}
		else{
			string path2="/usr/bin/";
			string fullPath1=path2+initialCommand;
			if(checkCommandExist(fullPath1) == 1){
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

