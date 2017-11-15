#include <string>

class Instruction {
	string binary

	public:
		Instruction();
		string getOpCode();
		string getdata();
		void setBinary();
}

Instruction::Instruction()
{

}

void setBinary(string line)
{
	binary = line;
}
