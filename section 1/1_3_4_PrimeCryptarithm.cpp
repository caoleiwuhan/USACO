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

using namespace std;

#define _MY_DEBUG_

int numbers[10];

int num;



/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

/*
	判断数字是否合法
*/
bool IsValidNum(int bits);

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/1.3.4 Prime Cryptarithm/input7.txt";
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
	cin >> num;
	for (int i = 0; i < num; ++i)
	{
		cin >> numbers[i];
	}
	int ans = 0;
	for (int i = 111; i < 1000; ++i)
	{
		if (!IsValidNum(i))
		{
			continue;
		}
		for (int j = 11; j < 100; ++j)
		{
			if (!IsValidNum(j))
			{
				continue;
			}
			int first = i * (j % 10);
			
			if (!IsValidNum(first) || (first > 999))
			{
				continue;
			}
			int second = i * (j / 10);
			
			if (!IsValidNum(second) || (second > 999))
			{
				continue;
			}
			int mul = i * j;
			if ((!IsValidNum(mul)) || (mul > 9999))
			{
				continue;
			}
			++ans;
		}
	}
	cout << ans << endl;
}

bool IsValidNum(int bits)
{
	while (bits)
	{
		bool isOK = false;
		int cur = bits % 10;
		for (int i = 0; i < num; ++i)
		{
			if (numbers[i] == cur)
			{
				isOK = true;
				break;
			}
		}
		if (!isOK)
		{
			return false;
		}
		bits /= 10;
	}
	return true;
}