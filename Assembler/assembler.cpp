#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <bitset>
#include <stdlib.h>

#include "assembler.h"
#include "instruction.h"

using namespace std;

Instruction accumulator;
Instruction p_Instruction;
Instruction c_Instruction;
vector<Instruction> store;

int main()
{
	init();
	
	for(unsigned int i=0; i < store.size(); i++)	//TODO: needs change based on file sizes
	{
		increment_CI();
		string current = fetch();
		decode(current);
		//execute();				//called from decode
		display();
	}
	
	
	return 0;
}

void init()
{
	ifstream file("testfile");			//TODO: check how file will be read and modify accordingly
	if(!file)
	{
		cout << "Unable to open file" << endl;
		return;
	}

	string line;
	while(getline(file, line))
	{
		Instruction x;
		x.setBinary(line);
		store.push_back(x);
	}


	for(unsigned int j=0; j < store.size(); j++)
	{
		c_Instruction.setBinary("00000000000000000000000000000000");
		p_Instruction.setBinary("00000000000000000000000000000000");
		accumulator.setBinary("00000000000000000000000000000000");
	}
}

//mm
void increment_CI()
{
	int CI_decimal = binToInt(c_Instruction.getBinary());
	CI_decimal++;
	cout << "CI_decimal: " << CI_decimal << endl;
	c_Instruction.setBinary(intToBin(CI_decimal));
}


//mf
string fetch()
{
	int CI_decimal = binToInt(c_Instruction.getBinary());
	cout << "...CI_decimal: " << CI_decimal << endl;
	return store[CI_decimal].getBinary();
}


//mf
void decode(string current)
{
	string opCode = current.substr(14, 3);
	string data = current.substr(0, 5);

	cout << endl << "opCode: " << opCode << endl;
	cout << "data: " << data << endl;

	if(opCode == "000")
		execute("JMP", binToInt(data));
	else if(opCode == "100")
		execute("JRP", binToInt(data));
	else if(opCode == "010")
		execute("LDN", binToInt(data));
	else if(opCode == "110")
		execute("STO", binToInt(data));
	else if(opCode == "001")
		execute("SUB", binToInt(data));
	else if(opCode == "101")
		execute("SUB", binToInt(data));
	else if(opCode == "011")
		execute("CMP", binToInt(data));
	else if(opCode == "111")
		execute("STP", binToInt(data));
	else
	{
		cout << "Unable to read command. Exiting..." << endl;
		return;
	}
}

//Converts a binary string to an int
long int binToInt(string binary)
{
	cout << "binToInt call..." << binary << endl;
	long int decimal = bitset<32>(binary).to_ulong();
	cout << "Decimal return..." << decimal << endl;
	return decimal;
}

//Converts an int to a binary string
string intToBin(int decimal)
{
	cout << "intToBin call..." << decimal << endl;
	bitset<32>bin_x(decimal);
	stringstream ss;
	ss << bin_x;
	string binary = ss.str();

	cout << "Binary return..." << binary << endl;
	return binary;
}


// uint32_t LittleToBig()
// {
// 	uint32_t b = varNum;
	
// 	b = ((b >> 1) & 0x55555555u) | ((b & 0x55555555u) << 1);
//     	b = ((b >> 2) & 0x33333333u) | ((b & 0x33333333u) << 2);
//     	b = ((b >> 4) & 0x0f0f0f0fu) | ((b & 0x0f0f0f0fu) << 4);
//     	b = ((b >> 8) & 0x00ff00ffu) | ((b & 0x00ff00ffu) << 8);
//     	b = ((b >> 16) & 0xffffu) | ((b & 0xffffu) << 16);	
// }

//mm
void execute(string opCode, int operand)
{

	if(opCode == "JMP"){
		//int CI_decimal = binToInt(c_Instruction.getBinary());
		cout << "Operand: " << operand << endl;
		c_Instruction.setBinary(intToBin(operand));
	}else if(opCode == "JRP"){
		cout << "Operand: " << operand << endl;
		int x = binToInt(c_Instruction.getBinary());
		c_Instruction.setBinary(intToBin(x-operand));
	}else if(opCode == "LDN"){	
	cout << "Operand: " << operand << endl;	
		accumulator.setBinary(intToBin(-(operand)));
	}else if("STO"){
		cout << "Operand: " << operand << endl;
		operand = binToInt(accumulator.getBinary());
	}else if("SUB"){
		cout << "Operand: " << operand << endl;
		int x = binToInt(accumulator.getBinary());
		accumulator.setBinary(intToBin(x-operand));
	}else if("CMP"){
		cout << "Operand: " << operand << endl;
		if(binToInt(accumulator.getBinary()) < 0)
			increment_CI();
	}else if("STP")
		exit(0);
}

void display()
{
   
	// int x=0;
	// while(store[x].getBinary() != "")
	// {
	// 	cout << store[x].getBinary() << endl;
	// 	x++;
	// }

	for(unsigned int i=0; i < store.size(); i++)
	{
		cout << store[i].getBinary() << endl;
	}
	
	cout << endl;
	cout << "accumulator: " << accumulator.getBinary() << endl;
	cout << "control insturction: " << c_Instruction.getBinary() << endl;
	cout << "present insturction: " << p_Instruction.getBinary() << endl;

	cout << endl << "data: " << p_Instruction.getData() << endl;
	cout << "opcode: " << p_Instruction.getOpCode() << endl;
}

