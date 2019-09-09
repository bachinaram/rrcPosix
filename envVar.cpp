#include<string>
#include<cstring>
#include <stdio.h>
#include<iostream>
#include<fstream>
#include<stdio.h>
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
	return eachLine;
}




//below function is used to keep the command record tracking in .r_history of HOME
void historyRecord(string inputCommand){
	ofstream histFile;
	histFile.open(".r_history",ios::in|ios::out|ios::app);
	histFile << inputCommand <<endl;
	histFile.close();
	}




void addNewVariable(string newVariable){
	ofstream envFile;
	envFile.open(".rrc",ios::in|ios::out|ios::app);
	envFile << newVariable <<endl;
	//cout<< newVariable;
	envFile.close();
}

string removeExport(string initCommand,string settingStr){

	size_t lineFirstPlace = initCommand.find(settingStr);
	initCommand.erase(lineFirstPlace, settingStr.length());
	return initCommand;
}

int searchStr(string searchString){
	ifstream envFile;
	string eachLine;
	int ll;
	envFile.open(".rrc");
	if(!envFile){
		cout << "something wrong with file, check if the file exist" << endl;
		return -1;
	}
	size_t pos;
	while(envFile.good())
	{
      getline(envFile,eachLine);
      pos=eachLine.find(searchString);
      if(pos!=string::npos)
        {
    	  	ll=0;
    	  	//cout<<"hi0";
    	  	break;
        }
      }
	envFile.close();
	return ll;
}


int updateOldVariable(string oldString,string newString){
	ifstream envFile;
	string eachLine;
	envFile.open(".rrc");
	if(!envFile){
		cout << "something wrong with file, check if the file exist" << endl;
		return -1;
	}


	ofstream envFileTmp;
	envFileTmp.open(".rrc_temp",ios::out);
	if (!envFileTmp){
		cout << "something wrong with tmp file, check if the file exist"<<endl;
	    return -1;
	}
	size_t oldStrLen = oldString.length();
	while (getline(envFile, eachLine))
	    {
	        while (true)
	        {
	            size_t pos = eachLine.find(oldString);
	            if (pos != string::npos)
	                eachLine.replace(pos, oldStrLen, newString);

	            else
	                break;
	        }

	        envFileTmp << eachLine << endl;
	    }
	envFile.close();
	envFileTmp.close();
	rename(".rrc_temp",".rrc");
	return 0;
}
