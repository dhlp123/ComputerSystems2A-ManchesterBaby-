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
	
	for(int i=0; i < 10; i++)		//TODO: needs change based on file sizes
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
		execute("JMP", 0);
	else if(opCode == "100")
		execute("JRP", 0);
	else if(opCode == "010")
		execute("LDN", 0);
	else if(opCode == "110")
		execute("STO", 0);
	else if(opCode == "001")
		execute("SUB", 0);
	else if(opCode == "101")
		execute("SUB", 0);
	else if(opCode == "011")
		execute("CMP", 0);
	else if(opCode == "111")
		execute("STP", 0);
	else
	{
		cout << "Unable to read command. Exiting..." << endl;
		exit(1);
	}



	
}

//Converts a binary string to an int
int binToInt(string binary)
{
	cout << "binToInt call..." << binary << endl;
	return 0;
}

//mm
void execute(string opCode, int operand)
{
	cout << "Opcode: " << opCode << endl;
	cout << "Operand: " << operand << endl;
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

