#include<iostream>
#include <unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<string>
#include<cstring>
using namespace std;
#include "operations.h"


/*
process execution happens at child process imp
we need to set wait(0) at parent for graceful termination of child process
*/

void cmdExecFuntion(string incommingCommd){

    string piperr = "|";
    size_t found = incommingCommd.find(piperr);
     if (found != string::npos){
    	pipeCmdExecution(incommingCommd);
     }
     else{
    	 string token1=incommingCommd;
    	char* chrString1 = const_cast<char*> (token1.c_str());
        char* cmdArg[token1.length()];
	//converting the method string to char array

	//converted char array is passed to strtok
	char* tk1=strtok(chrString1," ");
	int i=0;
	while (tk1 != NULL) {
		cmdArg[i]=tk1;
		//cout << token <<endl;
		tk1 = strtok(NULL, " ");
		i++;

	}

	//we really need to keep the last element in cmdAr as Null es args doesn't work
	cmdArg[i]=NULL;
	//cout << cmdArg[1]<<endl;

	pid_t processId = fork();
	if(processId > 0){
		wait(0);
		cout << "Parent process" << processId << endl;
	}
	else if(processId == 0){
		cout << "child created " << processId << endl;
		if(execvp(cmdArg[0],cmdArg)==-1){
					perror("exec");
					cout << "No command found"<<endl;
				}
	}
	else{
		cout << "error at process id creation - forking(issue)" << endl;
	}
     }
}
