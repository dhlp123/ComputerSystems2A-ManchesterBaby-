#include <string>

using std::string;

class Instruction {
	string binary;
	string OpCode;
	int data;

	public:
		Instruction();
		string getOpCode();
		string getdata();
		void setBinary(string line);
		string getBinary();
};

Instruction::Instruction()
{
	this->binary = "";
}

void Instruction::setBinary(string line)
{
	this->binary = line;
}

string Instruction::getBinary()
{
	return this->binary;
}

