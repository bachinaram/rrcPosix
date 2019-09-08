#include<fstream>
#include<string>
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


//above code returns 1 if the file exist and 0 if command not found


