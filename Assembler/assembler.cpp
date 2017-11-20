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
bool stop = false;

int main()
{

	init();

	for(unsigned int i=0; i < store.size() && stop == false; i++)	
	{
		cout << endl;
		cout << "LINE: " << i+1 << endl;
		cout << "###################################################" << endl;
		string current = fetch();
		decode(current);
		display();
		increment_CI();
		cout << "###################################################" << endl;
	}
	
	
	return 0;
}

void init()
{
	ifstream file("CompiledCode.txt");			
	if(!file)
	{
		cout << "Unable to open file" << endl;
		return;
	}

	string line;
	while(getline(file, line))
	{
		Instruction x;
		line.erase(line.find_last_not_of(" \n\r\t")+1);
		x.setBinary(line);
		store.push_back(x);
	}


	for(unsigned int j=0; j < store.size(); j++)
	{
		c_Instruction.setBinary("00000000000000000000000000000000");
		p_Instruction.setBinary("00000000000000000000000000000000");
		accumulator.setBinary("00000000000000000000000000000000");
	}
	file.close();
}

//mm
void increment_CI()
{
	int CI_decimal = binToInt(c_Instruction.getBinary());
	CI_decimal++;
	c_Instruction.setBinary(intToBin(CI_decimal));
}


//mf
string fetch()
{
	int CI_decimal = binToInt(c_Instruction.getBinary());
	return store[CI_decimal].getBinary();
}


//dp
int convertEndian(string data){

	int num, b;

	string newData;

	//For 8 bit conversion
	if(data.length() < 8){

		newData = data;

		if(data.length() != 8 && 8-data.length() > 0){
			for(unsigned int i=0; i<(8-data.length()); i++){
				newData = newData + "0";
			}
		}
		else { newData = data; }

		num = bitset<8>(newData).to_ulong();

		b = num;
	
		b = ((b >> 1) & 0x55555555u) | ((b & 0x55555555u) << 1);
	    	b = ((b >> 2) & 0x33333333u) | ((b & 0x33333333u) << 2);
	    	b = ((b >> 4) & 0x0f0f0f0fu) | ((b & 0x0f0f0f0fu) << 4);
		
	}
	//For 32 bit conversion
	else if(data.length() > 8){
		
		newData = data;
		
		if(data.length() > 32){
			for(unsigned int i=data.length(); i>32; i--){
				newData = newData.substr(0, newData.size()-1);
			}
		}
		else if(data.length() != 32 && 32-data.length() > 0){
			for(unsigned int i=0; i<(32-data.length()); i++){
				newData = newData + "0";
			}
		}
		else { newData = data; }

		
		num = bitset<32>(newData).to_ulong();

		b = num;
	
		b = ((b >> 1) & 0x55555555u) | ((b & 0x55555555u) << 1);
    		b = ((b >> 2) & 0x33333333u) | ((b & 0x33333333u) << 2);
    		b = ((b >> 4) & 0x0f0f0f0fu) | ((b & 0x0f0f0f0fu) << 4);
    		b = ((b >> 8) & 0x00ff00ffu) | ((b & 0x00ff00ffu) << 8);
    		b = ((b >> 16) & 0xffffu) | ((b & 0xffffu) << 16);

	}

	//Checking for negatives
	b = (int) binToInt(intToBin(b));
	
	return (int) b;
}

//dp
int getNumFromAddress(int address){
	if(address == 0){ return 0; }
	else{
		address++;

		int num = convertEndian(store[address-1].getBinary());

		int result = (int) bitset<32>(num).to_ulong();

		return (int) result;
	}
	return 0;
}

//mf
void decode(string current)
{
	string opCode = current.substr(13, 3);
	string data = current.substr(0, 5);
	int convData = (int) getNumFromAddress(convertEndian(data));

	cout << endl << "OpCode: " << opCode << endl;
	cout << "Data: " << convData << endl << endl;

	if(opCode == "000")
		execute("JMP", convData);
	else if(opCode == "100")
		execute("JRP", convData);
	else if(opCode == "010")
		execute("LDN", convData);
	else if(opCode == "110")
		execute("STO", convData);
	else if(opCode == "001")
		execute("SUB", convData);
	else if(opCode == "101")
		execute("SUB", convData);
	else if(opCode == "011")
		execute("CMP", convData);
	else if(opCode == "111"){
		execute("STP", convData);
	}
	else
	{
		cout << "Unable to read command. Exiting..." << endl;
		return;
	}
	return;
}

//Converts a binary string to an int
int binToInt(string binary)
{
	signed long int decimal;

	if(binary[0] == '1'){
		decimal = static_cast<long int>(bitset<32>(binary).to_ulong());
	}
	else{	
		decimal = bitset<32>(binary).to_ulong();
	}
	return (int) decimal;
}

//Converts an int to a binary string
string intToBin(int decimal)
{
	bitset<32>bin_x(decimal);
	stringstream ss;
	ss << bin_x;
	string binary = ss.str();

	return binary;
}


//mm
void execute(string opCode, int operand)
{
	if(opCode == "JMP"){
		c_Instruction.setBinary(intToBin(operand));
	}else if(opCode == "JRP"){
		int x = binToInt(c_Instruction.getBinary());
		c_Instruction.setBinary(intToBin(x-operand));
	}else if(opCode == "LDN"){	
		int x = -operand;
		accumulator.setBinary(intToBin(x));
	}else if(opCode == "STO"){	
		int i = findLine( (int) operand);
		store[i].setBinary(intToBin(convertEndian(accumulator.getBinary())));	
	}else if(opCode == "SUB"){
		int x = binToInt(accumulator.getBinary());
		accumulator.setBinary(intToBin((int) x-operand));
	}else if(opCode == "CMP"){
		if(binToInt(accumulator.getBinary()) < 0)
			increment_CI();
	}else if(opCode == "STP"){
		stop = true;
		return;
	}
	else{
		cout << "Execution error: Opcode not recognised" << endl;
		stop = true;
		return;
	}
}

//dp
int findLine(int num){

	int eNum = convertEndian(intToBin( (int) num));
	string bin = intToBin( (int) eNum);


	for(unsigned int i=0; i<store.size(); i++){

		if( (bin) == (store[i].getBinary()) && i != 0){
			return i;
		}
	}

	return 0;
}


void display()
{
	cout << "Memory: " << endl;
	for(unsigned int i=0; i < store.size(); i++)
	{
		cout << store[i].getBinary() << endl;
	}
	
	cout << endl;
	cout << "Accumulator Binary: " << accumulator.getBinary() << endl;
	cout << "Accumulator Value: " << binToInt(accumulator.getBinary()) << endl;

}

