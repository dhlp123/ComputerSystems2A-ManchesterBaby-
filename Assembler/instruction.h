#include <string>

using std::string;

class Instruction {
	string binary;
	string OpCode;
	int data;

	public:
		string getOpCode();
		string getdata();
		void setBinary(string line);
		string getBinary();
};

void Instruction::setBinary(string line)
{
	this->binary = line;
}

string Instruction::getBinary()
{
	return this->binary;
}

