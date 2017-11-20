#include <iostream>
#include <string.h>
#include <sstream>
#include <bitset>
#include <fstream>
#include <algorithm>
#include <vector>

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "compiler.h"

using namespace std;

/** 

NOTE: Since I have gotten the big endian conversion for the opCodes and Address numbers to work the only thing I have left to do is rewrite the conversion and reading methods to work with variable declaration and referencing.

**/

string opcode[] = {"JMP", "JRP", "LDN", "STO", "SUB", "SUB", "CMP", "STP"};
string opcodeBinary[] = {"000", "100", "010", "110", "001", "101", "011", "111"};
signed int opLen = (sizeof(opcode)/sizeof(opcode[0]));


vector<string> splitString(string str, string delim){
	vector<string> toks;
	stringstream ss(str);
	string line;

	while(getline(ss, line)){
		size_t pos, prev = 0;
		while((pos = line.find_first_of(delim, prev)) != string::npos){
			if(pos > prev){
				toks.push_back(line.substr(prev, pos-prev));
			}
			prev = pos+1;		
		}
		if(prev < line.length()){
			toks.push_back(line.substr(prev, string::npos));
		}	
	}

	return toks;
}


//Reads the Assembly code in from a file
//Calls the translate methods for each line.
void readCode(string fileName){
	ifstream file;

	file.open(fileName.c_str());

	string line;
	int lineNum = 0;
	vector<string> vars;


	//Getting Varaible Name Declarations
	while(getline(file, line)){

		vector<string> toks;
		stringstream ss; 

		toks = splitString(line, " ");

		if(toks[0].find(':') != string::npos && toks[1] == "VAR"){
			stringstream ss;
			ss << toks[0] << lineNum;
			vars.push_back(ss.str());
		}

		if(toks[0] != ";"){ lineNum++; }

	}
	
	file.close();

	file.open(fileName.c_str());

	cout << "Variables Loaded: " << vars.size() << endl;
	cout << "Starting to Read Lines" << endl;

	//Reading Lines
	while(getline(file, line)){
		
		string opCode, num;
		vector<string> toks;
		stringstream ss;

		toks = splitString(line, " :;");

		for(unsigned int i=0; i<toks.size(); i++){

			if(toks[i].find(':') != string::npos && toks[i+1] == "VAR"){
				if(toks[i+2] != ""){
					char * end;
					long int number = strtol(toks[i+2].c_str(), &end, 0);

					cout << toks[i]  << " " << toks[i+1] << " " << number << endl;

					translateCodeToBinary(number);
				}
			}
			else if(toks[i] == string("VAR")){
				if(toks[i+1] != ""){
					char * end;
					long int number = strtol(toks[i+1].c_str(), &end, 0);

					cout << toks[i]  << " " << number << endl;

					translateCodeToBinary(number);
				}
			}
			else{
				for(int op=0; op<opLen; op++){
					if(toks[i] == opcode[op]){
						opCode = toks[i];
						for(unsigned int v=0; v<vars.size(); v++){
							if(toks[i+1] != ""){
								
								vector<string> varToks;

								varToks = splitString(vars[v], ":");

								string varName = varToks[0];
								string varLine = varToks[1];
				
								if(toks[i+1] == varName){
									num = varLine;
									break;
								}
							}
						}
						if(num == ""){
							num = toks[i+1];
						}

						int number = atoi(num.c_str());

						cout << opCode << " " << number << endl;
		
						translateCodeToBinary(opCode, number);

						break;
					}
				}
			}
		}
	}
	file.close();
}

//Goes through the code line by line and translates it to it's binary form.
//This takes the opcode and the address and translates them to their binary big endian forms.
void translateCodeToBinary(string opCode, int num){
	
	string bitOp;

	for( int i=0; i < opLen; i++ ){
		if( opCode == opcode[i] ){
			bitOp = opcodeBinary[i];
			break;
		}
	}	
	
	//Convert to little endian, binary, and then a string.
	if(opCode != "STP"){
		stringstream ss;
		
		//~~~~~8 Bit Little Endian Conversion~~~~~//

		uint8_t b = num;
	
		b = ((b >> 1) & 0x55555555u) | ((b & 0x55555555u) << 1);
    		b = ((b >> 2) & 0x33333333u) | ((b & 0x33333333u) << 2);
    		b = ((b >> 4) & 0x0f0f0f0fu) | ((b & 0x0f0f0f0fu) << 4);	

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

		bitset<8> bin_x(b);
		ss << (bin_x);	

		string bitNum = ss.str();

		cout << bitOp << " " << bitNum << endl;
		
		translateBinaryToLine(bitNum, bitOp);
	}
	else{
		cout << bitOp << endl;
		
		translateBinaryToLine("00000", bitOp);
	}	
}

//Overloaded translation method for dealing with variable declaration.
void translateCodeToBinary(long int varNum){
	string varBin;
	stringstream ss;

	//~~~~~32 Bit Little Endian Conversion~~~~~//

	uint32_t b = varNum;
	
	b = ((b >> 1) & 0x55555555u) | ((b & 0x55555555u) << 1);
    	b = ((b >> 2) & 0x33333333u) | ((b & 0x33333333u) << 2);
    	b = ((b >> 4) & 0x0f0f0f0fu) | ((b & 0x0f0f0f0fu) << 4);
    	b = ((b >> 8) & 0x00ff00ffu) | ((b & 0x00ff00ffu) << 8);
    	b = ((b >> 16) & 0xffffu) | ((b & 0xffffu) << 16);	

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

	bitset<32> bin_x(b);

	ss << bin_x;
	
	varBin = ss.str();

	cout << "Generated 32 bit Line:" << endl;

	cout << varBin << endl << endl;
	
	writeMachineCode(varBin);	
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
	cout << bLine << endl << endl;

	writeMachineCode(bLine);

}

//Takes the 32 bit line and writes it into a line of the output file for the compiled code.
//If there is no file avaiable it should create one and write to it.
void writeMachineCode(string line){
	ofstream file("../Assembler/CompiledCode.txt", std::ios_base::app);

	file << line << endl;

	file.close();
}


//Main function for the methods calls to take place.
int main(){
	remove("CompiledCode.txt");
	readCode("AssemblyCode.txt");
	
	return 0;
}


