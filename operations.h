#include<string>
using namespace std;
string readEnvFile(string promptString);
int readEnvFile1(string promptString);
void historyRecord(string inputCommand);
void setPromptString();
void inputArgs();
bool checkCommandExist(string scmd);
void cmdExecFuntion(string incommingCommd);
void getHistory();
void addNewVariable(string newVariable);
string removeExport(string initCommand,string settingStr);
int searchStr(string searchString);
int updateOldVariable(string oldString,string newString);
void aliasCheck(string aliasExclusionCommad);
