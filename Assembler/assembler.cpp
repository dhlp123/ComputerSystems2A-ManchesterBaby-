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
void fetch()
{
	//convert c_instruction to decimal
	//int CI_decimal = ...
	//store[CI_decimal].getBinary()
	//return CI_instruction
}


//mf
void decode()
{
	//string opCode = CI_instruction.getOpCode()
	//CI_instruction.getData()
	//
	//switch(opCode) {
	//	case "VAR":
	// 		do something
	// 		break;
	//	case "LDN":
	//		do something
	//	default:
		// 	cout << "Error reading file" << endl;
		// 	exit(1);
		// 	break;
		// }
	//}




// 	; THIS PROGRAM ADDS TWO NUMBERS TOGETHER
// ; The program starts at address 1, so we need to pad out address 0 
//           VAR 0       ; Declare 32-bit variable to fill space 
// START:    LDN NUM01   ; Copy variable to accumulator (negated)
//           SUB NUM02   ; Subtract variable from accumulator to get sum (negated)
//           STO MYSUM   ; Store accumulator to variable - saves answer
// ; The next two instructions negate the stored answer
//           LDN MYSUM   ; Copy variable to accumulator (negated)
//           STO MYSUM   ; Store accumulator to variable
// END:      STP         ; Stop processor
// ; Variable declarations follow
// NUM01:    VAR 1025    ; Declare 32-bit variable
// NUM02:    VAR 621     ; Declare 32-bit variable
// MYSUM:    VAR 0       ; Declare 32-bit variable

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
}

