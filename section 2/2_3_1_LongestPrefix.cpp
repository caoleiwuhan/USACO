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

const int MAXV = 201;

//string primitive[MAXV];

//int prefix[200001][201];

bool s[200001];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();


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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/2.3.1 Longest Prefix/input2.txt";
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
	//int count = 0;
	string str;
	set<string> primitive;
	int pLen = 0;
	while (cin >> str)
	{
		if (str == ".")
		{
			break;
		}
		primitive.insert(str);
		if (str.length() > pLen)
		{
			pLen = str.length();
		}

		//primitive[count++] = str;
	}

	string sequence = "";
	while (getline(cin, str))
	{
		sequence += str;
	}

	s[0] = true;
	int len = sequence.length();
	// 如果有连续pLen个没有，则不必再搜索
	int last = 0;
	int maxLen = -1;
	for (int i = 1; i <= len; ++i)
	{
		int end = i - pLen;
		if (end < 0)
		{
			end = 0;
		}
		for (int j = i - 1; j >= end; --j)
		{
			if (s[j])
			{
				string tmp = sequence.substr(j, i - j);
				if (primitive.find(tmp) != primitive.end())
				{
					s[i] = true;
					last = 0;
					break;
				}
			}
		}
		if (!s[i])
		{
			++last;
		}
		if (last >= pLen)
		{
			maxLen = i;
			break;
		}
	}
	if (maxLen == -1)
	{
		maxLen = sequence.length();
	}
	for (int i = maxLen; i >= 0; --i)
	{
		if (s[i])
		{
			cout << i << endl;
			break;
		}
	}
}
