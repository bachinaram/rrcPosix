#include<iostream>
#include <unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<string>
#include<cstring>
#include <stdlib.h>
#include <sys/types.h>
#include<sstream>
using namespace std;
#include "operations.h"
#define OUTPUT_END 0
#define INPUT_END 1

/*
process execution happens at child process imp
we need to set wait(0) at parent for graceful termination of child process
*/

void pipeCmdExecution(string incommingCommd){

	//string incommingCommd="ls -ltr | wc";
	stringstream ss(incommingCommd);
	//string myPath="/bin/";
	string token;
	string token1; //
	string token2;
	string token3;

	while(getline(ss, token, '|')) {
	    if(token1.empty()){
	    	token1 = token;
	    	//cout << token1 << '\n';

	    }
	    else if(token2.empty()){
	    	token2 = token;
	    	//cout << token2 << '\n';

	    }
	    else{
	    	token3 = token;
	    	//cout << token3 << '\n';

	    }

	}

		char* chrString1 = const_cast<char*> (token1.c_str());
		char* chrString2 = const_cast<char*> (token2.c_str());
		char* cmdArg1[token1.length()];
		char* cmdArg2[token2.length()];
		//char* cmdArg3[token3.length()];
		//converting the method string to char array



		char* tk1=strtok(chrString1," ");
		int i=0;
		while (tk1 != NULL) {
			cmdArg1[i]=tk1;
			//cout << tk1 <<endl;
			tk1 = strtok(NULL, " ");
			i++;
		}

		char* tk2=strtok(chrString2," ");
		int j=0;
		while (tk2 != NULL) {
			cmdArg2[j]=tk2;
			//cout << tk2 <<endl;
			tk2 = strtok(NULL, " ");
			j++;
		}
	/*
		char* tk3=strtok(chrString3," ");
		int k=0;
		while (tk3 != NULL) {
			cmdArg3[k]=tk3;
			//cout << tk3 <<endl;
			tk3 = strtok(NULL, " ");
			k++;
		}
	*/
		//we really need to keep the last element in cmdAr as Null es args doesn't work

		cmdArg1[i]=NULL;
		cmdArg2[j]=NULL;

	//cmdArg3[k]=NULL;



	int pipes[2];
	pipe(pipes);
	pid_t processId1 = fork();
	if(processId1==0){
		close(pipes[INPUT_END]);
        dup2(pipes[OUTPUT_END], STDIN_FILENO);
        close(pipes[OUTPUT_END]);
        execvp(cmdArg2[0],cmdArg2);
	}
	else{
        pid_t processId2=fork();
        if(processId2==0)
        {
            close(pipes[OUTPUT_END]);
            dup2(pipes[INPUT_END], STDOUT_FILENO);
            close(pipes[INPUT_END]);
			execvp(cmdArg1[0],cmdArg1);
        }

        close(pipes[OUTPUT_END]);
        close(pipes[INPUT_END]);
        waitpid(-1, NULL, 0);
        waitpid(-1, NULL, 0);

    }

}
