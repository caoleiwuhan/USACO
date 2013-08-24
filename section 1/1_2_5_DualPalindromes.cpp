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

string baseMap = "0123456789ABCDEFGHIJ";

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

/*
	将数转化为以base为进制的string
*/
string TransNum(int num, int base);

/*
	判断是否是回文数
*/
bool IsPalindromic(string str);



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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/1.2.5 Dual Palindromes/input7.txt";
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
	// 进制
	int n;
	int s;
	string str;

	cin >> n >> s;
	++s;

	while (n)
	{
		int count = 0;
		for (int i = 2; i <= 10; ++i)
		{
			str = TransNum(s, i);
			if (IsPalindromic(str))
			{
				++count;
				if (count >= 2)
				{
					cout << s << endl;				
					--n;
					break;
				}
			}
		}
		++s;
	}	
}

string TransNum(int num, int base)
{
	string ans;
	while (num)
	{
		int reminder = num % base;
		ans.append(1, baseMap[reminder]);
		num = num / base;
	}
	int size = ans.length();
	int len = size / 2;
	for (int i = 0; i < len; ++i)
	{
		char tmp = ans[size - 1 - i];
		ans[size - 1 - i] = ans[i];
		ans[i] = tmp;		
	}
	return ans;
}

bool IsPalindromic(string str)
{
	int size = str.length();
	int len = size / 2;
	for (int i = 0; i < len; ++i)
	{
		if (str[i] != str[size - 1 - i])
		{
			return false;
		}
	}
	return true;
}