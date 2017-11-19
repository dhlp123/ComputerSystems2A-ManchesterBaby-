#include <string>

using std::string;

class Instruction {
	string binary;

	public:
		Instruction();
		string getOpCode();
		string getData();
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

std::string Instruction::getBinary()
{
	return this->binary;
}

string Instruction::getOpCode()
{
	return this->binary.substr(14, 3);
}

string Instruction::getData()
{
	return this->binary.substr(0, 5);
}


