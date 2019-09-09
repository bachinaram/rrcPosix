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
	const string aliasStr= "alias ";
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
	else if(initialCommand.find(aliasStr) != string::npos){
		//adding a alias to environment
		string setCommand =  removeExport(initialCommand,aliasStr);
		string aliaCommand=setCommand;
		//cout << aliaCommand;
		addNewVariable(aliaCommand);
		setPromptString();
	}
	else{
		//below code check for the given command in /bin and /usr/bin dir and calls methods in commandoperations.cpp
		int searchResult = searchStr(initialCommand);
		cout<<initialCommand;
		if(searchResult == 0){
			string setVariable = initialCommand+setter;
			//cout<< setVariable;
			string aliasExclusionCommad = readEnvFile(setVariable);
			//cout<<aliasExclusionCommad;
			aliasCheck(aliasExclusionCommad);
			setPromptString();

		}
		else{
			aliasCheck(initialCommand);
			setPromptString();
		}

	}
}

