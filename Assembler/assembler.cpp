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
	
	int i;
	cout << "Please enter an line for an address number" << endl;
	cin >> i;
	cout << getNumFromAddress(i) << endl;

	//for(unsigned int i=0; i < store.size(); i++)	//TODO: needs change based on file sizes
	//{
	//	increment_CI();
	//	string current = fetch();
	//	decode(current);
	//	display();
	//}
	
	
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
	file.close();
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


//dp
long int convertEndian(string data){

	cout << "Data Endian Converted: " << data << endl;

	long int num, b;
	string newData;

	//For 8 bit conversion
	if(data.length() < 8){

		newData = data;

		if(data.length() != 8 && 9-data.length() > 0){
			for(unsigned int i=0; i<(9-data.length()); i++){
				cout << "8 Loop Running" << endl;
				newData = newData + "0";
			}
			cout << "8bit New Data: " << newData << endl;
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
				cout << "32 Loop Running: " << (newData) << endl;
				newData = newData.substr(0, newData.size()-1);
			}
		}
		else if(data.length() != 32 && 32-data.length() > 0){
			for(unsigned int i=0; i<(33-data.length()); i++){
				cout << "32 Loop Running: " << (data) << endl;
				newData = newData + "0";
			}
			cout << "32bit New Data: " << newData << "Length: " << newData.length() << endl;
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
	
	cout << "Endian conversion from: " << newData << " To: " << b << endl;

	return b;
}

//dp
int getNumFromAddress(int address){
	if(address == 0){ return 0; }
	
	cout << "Address: " << address << endl;
	cout << "Store Value Passed In: " << store[address].getBinary() << endl;

	int num = convertEndian(store[address].getBinary());

	cout << "Endian Value Returned: " << num << endl;

	int result = bitset<32>(num).to_ulong();
	
	cout << "Number at address " << address << " : " << result << endl;
	cout << store[address].getBinary().length() << endl;

	return result;
}

//mf
void decode(string current)
{
	string opCode = current.substr(14, 3);
	string data = current.substr(0, 5);
	long int convData = getNumFromAddress(convertEndian(data));

	cout << endl << "opCode: " << opCode << endl;
	cout << "data: " << convData << endl;

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
	else if(opCode == "111")
		execute("STP", convData);
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

