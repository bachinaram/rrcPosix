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

	char* cmdArg[50];
	//converting the method string to char array
	char chrString[incommingCommd.length()];
	for(int i=0;i<sizeof(chrString);i++){
		chrString[i] = incommingCommd[i];
	}


	//converted char array is passed to strtok
	char* token=strtok(chrString," ");
	int i=0;
	while (token != NULL) {
		cmdArg[i]=token;
		//cout << token <<endl;
		token = strtok(NULL, " ");
		i++;

	}

	//we really need to keep the last element in cmdAr as Nul les args doesn't work
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
