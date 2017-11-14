#include <iostream>
#include <vector>
#include "assembler.h"
#include "instruction.h"

using namespace std;

Instruction accumulator;
Instruction p_Instruction;
Instruction c_Instruction;
vector<Instruction> store(32);


int main()
{
	cout << "start" << endl;
	init();
	
	bool finish = false;
	
	//while(!finish)
	//{
		increment_CI();
		fetch();
		decode();
		execute();
		display();
	//}
	
	cout << "end" << endl;
	return 0;
}

void init()
{
	for (int j=0; j < 32; j++)
	{
		store[j].setBinary("00000000000000000000000000000000");
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
void fetch()
{

}


//mf
void decode()
{

}

//mm
void execute()
{

}

void display()
{

		for(int j = 0; j < 32; j++)
		{
			cout << store[j].getBinary() << endl;
		}
		cout << endl;
	

	cout << "accumulator: " << accumulator.getBinary() << endl;
	cout << "control insturction: " << c_Instruction.getBinary() << endl;
	cout << "present insturction: " << p_Instruction.getBinary() << endl;
}

