#include<string>
#include<cstring>
#include <stdio.h>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;
#include "operations.h"

bool checkCommandExist(string scmd){
	string firstWord;
	stringstream iss(scmd);
	iss >> firstWord;
	ifstream file(firstWord.c_str());
	return file.good();
}

void aliasCheck(string aliasExclusionCommad){
	string path1 = "/bin/";
	string fullPath=path1+aliasExclusionCommad;
	if(checkCommandExist(fullPath) == 1){
		//cout<<fullPath;
		cmdExecFuntion(fullPath);
		//need to above line and write a program to execute cmdExecution.cpp

		}
	else{
		string path2="/usr/bin/";
		string fullPath1=path2+aliasExclusionCommad;
		if(checkCommandExist(fullPath1) == 1){
			cmdExecFuntion(fullPath1);

			}
		else{
			cout << "command not exist"<<endl;

			}
		}

}


//above code returns 1 if the file exist and 0 if command not found


