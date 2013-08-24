#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <list>
#include <cstring>

using namespace std;

#define _MY_DEBUG_

// 字典中字的最大数
const int MAXV = 5001;
// 手机上的键值：一个8个，从2到9
const int KEYNUM = 8;

// 字典
string dict[MAXV];
// 字典中对于的数字
long long dictNum[MAXV];


char Map[KEYNUM][3] =
{
	'A', 'B', 'C',
	'D', 'E', 'F',
	'G', 'H', 'I',
	'J', 'K', 'L',
	'M', 'N', 'O',
	'P', 'R', 'S',
	'T', 'U', 'V',
	'W', 'X', 'Y'	
};




/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

/*
	通过字母返回数字
*/
int CharToNumber(char ch);

/*
	word，计算数字
*/
long long WordToNumber(string word);

// 打印字典
void PrintDict(int count);

/*
	ID: raycao
	PROG: transform
	LANG: C++
*/
int main()
{
	MainStructure();
	return 0;
}

void MainStructure()
{
	
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/1.2.3 Name That Number/input15.txt";
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
	// 读入字典
	ifstream fDict("C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/1.2.3 Name That Number/dict.txt");
	int count = 0;
	string word;
	while (fDict >> word)
	{
		dict[count++] = word;		
	}
	//PrintDict(count);
	// 排序
	sort(dict, dict + count);

	//PrintDict(count);

	// 计算word对应的数字
	for (int i = 0; i < count; ++i)
	{
		//long long tmp = WordToNumber(dict[i]);
		dictNum[i] = WordToNumber(dict[i]);
	}
	bool hasResult = false;
	long long fromNum;
	cin >> fromNum;
	for (int i = 0; i < count; ++i)
	{
		if (dictNum[i] == fromNum)
		{
			cout << dict[i] << endl;
			hasResult = true;
		}
	}
	if (!hasResult)
	{
		cout << "NONE" << endl;
	}
}


int CharToNumber(char ch)
{
	for (int i = 0;i < KEYNUM; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (Map[i][j] == ch)
			{
				return (i + 2);
			}
		}
	}
	return -1;
}

long long WordToNumber(string word)
{
	long long ans = 0;
	int len = word.length();
	for (int i = 0; i < len; ++i)
	{
		int num = CharToNumber(word[i]);
		ans = ans * 10 + num;
	}
	return ans;
}

void PrintDict(int count)
{
	for (int i = 0; i < count; ++i)
	{
		cout << dict[i] << endl;
	}
	cout << "-------------------------------------" << endl;
}