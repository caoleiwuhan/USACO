#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define _MY_DEBUG_

const int MAXV = 11;

// person name;
string names[MAXV];
// 付出
int output[MAXV];
// 收入
int input[MAXV];





/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

int FindIndexByStr(int numPerson, string str);


int main()
{
	MainStructure();
	return 0;
}

void MainStructure()
{
	
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/1.1.2 Greedy Gift Givers/gift1.in9";
	//string inputStr = "D:/2挑战编程/input/110205.inp";
	string outputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/1.outp";
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
	int count = 0;
	string str;
	while (getline(cin, str))
	{
		if (str == "")
		{
			break;
		}
		int numPerson = 0;
		stringstream ss(str);
		ss >> numPerson;
		for (int i = 0; i < numPerson; ++i)
		{
			cin >> names[i];
		}
		for (int i = 0; i < numPerson; ++i)
		{
			string curName;
			cin >> curName;
			int curIndex = FindIndexByStr(numPerson, curName);
			// 准备送出去的钱
			int price = 0;
			// 人数
			int num = 0;
			// 每个人要得到的钱
			cin >> price >> num;
			if (price == 0 || num == 0)
			{
				continue;
			}
			int singleMoney = price / num;

			// 送出去的钱数
			output[curIndex] -= singleMoney * num;
			
			for (int j = 0; j < num; ++j)
			{
				string friendName;
				cin >> friendName;
				int friendIndex = FindIndexByStr(numPerson, friendName);
				output[friendIndex] += singleMoney;
			}
		}
		if (count)
		{
			cout << endl;
		}
		++count;

		for (int i = 0; i < numPerson; ++i)
		{
			
			cout << names[i] << ' ' << (output[i]) << endl;
		}
		//cin.ignore();
	}

}

int FindIndexByStr(int numPerson, string str)
{
	for (int i = 0; i < numPerson; ++i)
	{
		if (names[i] == str)
		{
			return i;
		}
	}
	return -1;
}