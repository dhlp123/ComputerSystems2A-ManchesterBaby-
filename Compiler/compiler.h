#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

vector<string> splitString(string str, string delims);

void readCode(string fileName);
void translateCodeToBinary(string opCode, int num);
void translateCodeToBinary(long int varNum);
void translateBinaryToLine(string num, string opCode);
void writeMachineCode(string line);

