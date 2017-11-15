#include <string>
#include <stdlib.h>

using namespace std;

void readCode(string fileName);
void translateCodeToBinary(string opCode, int num);
void translateBinaryToLine(string num, string opCode);
void writeMachineCode(string line);

