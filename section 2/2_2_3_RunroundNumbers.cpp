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
#include <cctype>
#include <queue>
#include <cmath>


using namespace std;

#define _MY_DEBUG_

// 存放数字
char digits[30];

// 每个数字只能出现一次
bool used[30];



/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

bool IsRunroundNumber(unsigned num);

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/2.2.3 Runaround Numbers/input7.txt";
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
	unsigned long start;
	cin >> start;
	++start;
	while (true)
	{
		if (IsRunroundNumber(start))
		{
			cout << start << endl;
			break;
		}
		++start;
	}

}

bool IsRunroundNumber(unsigned num)
{
	memset(digits, 0, sizeof(digits));
	memset(used, 0, sizeof(used));
	int count = 0;
	while (num)
	{
		int remain = num % 10;
		if (remain == 0)
		{
			return false;
		}
		num /= 10;
		digits[count++] = remain;
		if (used[remain])
		{
			return false;
		}
		used[remain] = true;
	}
	memset(used, 0, sizeof(used));
	// 一共count次
	int pos = count;
	int begin = digits[pos-1];
	int init = begin;
	used[begin] = true;
	for (int i = 1; i < count; ++i)
	{
		pos = pos - begin;
		while (pos <= 0)
		{
			pos += count;
		}
		begin = digits[pos - 1];
		if (used[begin])
		{
			return false;
		}
		used[begin] = true;
	}
	pos = pos - begin;
	while (pos <= 0)
	{
		pos += count;
	}
	if (digits[pos-1] != init)
	{
		return false;
	}
	return true;
}