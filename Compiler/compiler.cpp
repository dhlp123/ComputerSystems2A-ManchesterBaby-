#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <fstream>
#include <algorithm>

#include <stdlib.h>
#include "compiler.h"

using namespace std;

/** 

NOTE: Since I have gotten the big endian conversion for the opCodes and Address numbers to work the only thing I have left to do is rewrite the conversion and reading methods to work with variable declaration and referencing.

**/

string opcode[] = {"JMP", "JRP", "LDN", "STO", "SUB", "SUB", "CMP", "STP"};
string opcodeBinary[] = {"000", "100", "010", "110", "001", "101", "011", "111"};

//Reads the Assembly code in from a file
//Calls the translate methods for each line.
void readCode(string fileName){
	ifstream file(fileName.c_str());

	string opCode, num;

	while(file >> opCode >> num){
		num.erase(remove(num.begin(), num.end(), ';'), num.end());
		
		int number = atoi(num.c_str());

		cout << opCode << " " << number << endl;
		
		translateCodeToBinary(opCode, number);
	}

	file.close();
}

//Goes through the code line by line and translates it to it's binary form.
//This takes the opcode and the address and translates them to their binary big endian forms.
void translateCodeToBinary(string opCode, int num){
	
	string bitOp;
	signed int opLen = (sizeof(opcode)/sizeof(opcode[0]));


	for( int i=0; i < opLen; i++ ){
		if( opCode == opcode[i] ){
			bitOp = opcodeBinary[i];
			break;
		}
	}

	//Convert int to byte.
	unsigned int b = (unsigned int) num;	
	
	//Convert byte to little endian, binary, and then a string.
	stringstream ss;
	
	b ^= 0xFFFF;
	
	bitset<5> bin_x(b);
	ss << (bin_x);	

	string bitNum = ss.str();

	cout << bitOp << " " << bitNum << endl;

	translateBinaryToLine(bitNum, bitOp);

}

//Takes the binary of each lines address and opcode.
//Then puts it into a 32 bit integer.
void translateBinaryToLine(string num, string opCode){

	string bLine = "00000000000000000000000000000000";

	//Num Insertion
	for( int i=0; i<5; i++ ){
		bLine[i] = num[i];
	}

	//OpCode Insertion
	
	bLine[13] = opCode[0];
	bLine[14] = opCode[1];
	bLine[15] = opCode[2];

	cout << "Generated 32 bit Line:" << endl;
	cout << bLine << endl;

	writeMachineCode(bLine);

}

//Takes the 32 bit line and writes it into a line of the output file for the compiled code.
//If there is no file avaiable it should create one and write to it.
void writeMachineCode(string line){
	ofstream file("CompiledCode.txt", std::ios_base::app);

	file << line << endl;

	file.close();
}


//Main function for the methods calls to take place.
int main(){
	remove("CompiledCode.txt");
	readCode("AssemblyCode.txt");
	
	return 0;
}


