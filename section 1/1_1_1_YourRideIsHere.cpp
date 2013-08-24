#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define _MY_DEBUG_

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();


int main()
{
	MainStructure();
	return 0;
}

void MainStructure()
{
	
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.inp";
	//string inputStr = "D:/2挑战编程/input/110205.inp";
	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/0000001.outp";
	ifstream fin;
	fin.open(inputStr);	

	cin.rdbuf(fin.rdbuf());	

	ofstream fout;
	fout.open(outputStr);

	//cout.rdbuf(fout.rdbuf());
#endif

	Process();
		
}

void Process()
{
	string str;
	while (getline(cin, str))
	{
		if (str == "")
		{
			break;
		}

		string comet;
		string group;
		stringstream ss(str);
		ss >> comet >> group;

		unsigned ansComet = 1;
		for (int i = 0; i < comet.length(); ++i)
		{
			ansComet *= (comet[i] - 'A' + 1);
			ansComet %= 47;
		}
		unsigned ansGroup = 1;
		for (int i = 0; i < group.length(); ++i)
		{
			ansGroup *= (group[i] - 'A' + 1);
			ansGroup %= 47;
		}
		if (ansComet == ansGroup)
		{
			cout << "GO" << endl;
		}
		else
		{
			cout << "STAY" << endl;
		}
	}
}

