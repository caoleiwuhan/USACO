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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/1.2.4 Palindromic Squares/input4.txt";
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
	int base;
	int square;
	string str;

	cin >> base;
	for (int i = 1; i <= 300; ++i)
	{
		// 平方数
		square = i * i;
		// 转换到base进制
		str = TransNum(square, base);
		// 判断str是否是回文数
		if (IsPalindromic(str))
		{
			cout << TransNum(i, base) << ' ' << str << endl;
		}
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