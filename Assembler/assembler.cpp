#include <iostream>
#include <vector>
#include <fstream>

#include "assembler.h"
#include "instruction.h"

using namespace std;

Instruction accumulator;
Instruction p_Instruction;
Instruction c_Instruction;
vector<Instruction> store(32);



int main()
{

	init();
	
	bool finish = false;
	
	for(int i=0; i < 10; i++)
	{
		increment_CI();
		string current = fetch();
		decode(current);
		execute();
		display();
	}
	
	
	return 0;
}

void init()
{
	ifstream file("testfile");
	if(!file)
	{
		cout << "Unable to open file" << endl;
		exit(1);
	}

	int x = 0;
	string line;
	while(getline(file, line))
	{
		store[x].setBinary(line);
		x++;
	}


	for (int j=0; j < 32; j++)
	{
		c_Instruction.setBinary("00000000000000000000000000000000");
		p_Instruction.setBinary("00000000000000000000000000000000");
		accumulator.setBinary("00000000000000000000000000000000");
	}
}

//mm
void increment_CI()
{

}

//mf
string fetch()
{
	int CI_decimal = binToInt(c_Instruction.getBinary());
	
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
		cout << "JMP" << endl;
	else if(opCode == "100")
		cout << "JRP" << endl;
	else if(opCode == "010")
		cout << "LDN" << endl;
	else if(opCode == "110")
		cout << "STO" << endl;
	else if(opCode == "001")
		cout << "SUB" << endl;
	else if(opCode == "101")
		cout << "SUB" << endl;
	else if(opCode == "011")
		cout << "CMP" << endl;
	else if(opCode == "111")
		cout << "STP" << endl;
	else
	{
		cout << "Unable to read file. Exiting..." << endl;
		exit(1);
	}



	
}

//Converts a binary string to an int
int binToInt(string binary)
{
	return 0;
}

//mm
void execute()
{

}

void display()
{
   
	int x=0;
	while(store[x].getBinary() != "")
	{
		cout << store[x].getBinary() << endl;
		x++;
	}
	
	cout << endl;
	cout << "accumulator: " << accumulator.getBinary() << endl;
	cout << "control insturction: " << c_Instruction.getBinary() << endl;
	cout << "present insturction: " << p_Instruction.getBinary() << endl;

	cout << endl << "data: " << p_Instruction.getData() << endl;
	cout << "opcode: " << p_Instruction.getOpCode() << endl;
}

