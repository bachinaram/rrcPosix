#include<string>
using namespace std;
string readEnvFile(string promptString);
void historyRecord(string inputCommand);
void setPromptString();
void inputArgs();
bool checkCommandExist(string scmd);
void cmdExecFuntion(string incommingCommd);
