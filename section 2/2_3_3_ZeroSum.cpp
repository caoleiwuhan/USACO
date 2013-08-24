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

int N;


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

void DFS(string str, int step);

bool ParseString(string str);

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/2.2.3 Zero Sum/input7.txt";
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

	cin >> N;
	//ParseString("1+2-3+4-5-6+7");
	//ParseString("1+2-3-4+5+6-7");
	//ParseString("1-2 3+4+5+6+7");
	//ParseString("1-2 3-4 5+6 7");
	//ParseString("1-2+3+4-5+6-7");
	//ParseString("1-2-3-4-5+6+7");

	DFS("1", 2);

}

void DFS(string str, int step)
{
	if (step > N)
	{
		if (ParseString(str))
		{
			cout << str << endl;
		}
	}
	else
	{
		string strTmp1 = str;
		strTmp1.append(1, ' ');

		char ch = char(step + '0');

		strTmp1.append(1, ch);
		DFS(strTmp1, step + 1);

		string strTmp2 = str;
		strTmp2.append(1, '+');
		
		strTmp2.append(1, ch);

		DFS(strTmp2, step + 1);

		string strTmp3 = str;
		strTmp3.append(1, '-');
		
		strTmp3.append(1, ch);
		DFS(strTmp3, step + 1);
		
	}
}



bool ParseString(string str)
{
	int sum = 1;
	// 首先解析出第一个
	int index = 1;
	int len = str.length();
	while ((index < len) && (str[index] == ' '))
	{		
		++index;
		int tmp = str[index++] - '0';
		sum = sum * 10 + tmp;		
	}
	
	while (index < len)
	{
		char sign = str[index++];
		// 解析下一个数字
		int num2 = str[index++] - '0';
		while ((index < len) && (str[index] == ' '))
		{		
			++index;
			int tmp = str[index++] - '0';
			num2 = num2 * 10 + tmp;		
		}
		if (sign == '+')
		{
			sum += num2;
		}
		else
		{
			sum -= num2;
		}
	}
	if (sum == 0)
	{
		return true;
	}
	return false;
}