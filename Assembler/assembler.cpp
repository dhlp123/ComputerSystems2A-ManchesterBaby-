#include <iostream>

using namespace std;

int p_Instruction[32];
int c_Instruction[32];
int accumulator[32];
int store[32][32];

void increment_CI();
void fetch();
void decode();
void execute();
void display();
void init();

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
	for(int i = 0; i < 32; i++)
	{
		c_Instruction[i] = 0;
		p_Instruction[i] = 0;
		accumulator[i] = 0;
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
	for(int i = 0; i < 32; i++)
	{
		for(int j = 0; j < 32; j++)
		{
			if(store[i][j] == 1)
				cout << "1 ";
			else
				cout << "0 ";
		}
		cout << endl;
	}

	cout << "accumulator: " << endl;
	cout << "control insturction: " << endl;
	cout << "present insturction: " << endl;
}

