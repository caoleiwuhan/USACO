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

int arr[10];

/*
	一、
	1.找出质数
	2.判断是否是回文数
	二、
	1.找出回文数
	2.判断是否是质数
*/

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

/*
	是否是回文数
*/
bool IsPalindr(int num);

bool Prin(int num, int &t1, int &t2);

bool Prin2(int num, int &t1, int &t2);

/*
	判断是否质数
*/
bool IsPrime(int num);

void TestPrim(int tmp, int a, int b, set<int> &ans);


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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/1.5.2 Prime Palindromes/pprime.in9";
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
	int a, b;
	cin >> a >> b;
	set<int> ans;

	// 最大为4个loop
	for (int d1 = 0; d1 <= 9; d1 += 1)
	{// 首尾的位：必须为奇数
		for (int d2 = 0; d2 <= 9; ++d2)
		{
			for (int d3 = 0; d3 <= 9; ++d3)
			{
				for (int d4 = 0; d4 <= 9; ++d4)
				{
					//int num = d1 + d2 * 10 + d3 * 100 + d4 * 1000;
					int num1 = d1 * 1000 + d2 * 100 + d3 * 10 + d4;
					// 翻转生成回文数1
					// 以d4为轴翻转，生成回文数2
					
					int tmp1, tmp2;
					if (Prin2(num1, tmp1, tmp2))
					{
						TestPrim(num1, a, b, ans);
					}
					TestPrim(tmp1, a, b, ans);
					TestPrim(tmp2, a, b, ans);	

					//int num2 = d1 * 1000 + d2 * 100 + d3 * 10 + d4;
					int num = d1 + d2 * 10 + d3 * 100 + d4 * 1000;

					if (Prin2(num, tmp1, tmp2))
					{
						TestPrim(num, a, b, ans);
					}
					TestPrim(tmp1, a, b, ans);
					TestPrim(tmp2, a, b, ans);
				}
			}
		}
	}
	for (set<int>::iterator itr = ans.begin(); itr != ans.end(); ++itr)
	{
		cout << *itr << endl;
	}

}

bool Prin(int num, int &t1, int &t2)
{
	int index = 0;
	while (num)
	{
		arr[index++] = num % 10;
		num /= 10;
	}
	bool isPalindro = true;
	for (int i = 0; i < index / 2; ++i)
	{
		if (arr[i] != arr[index - 1 - i])
		{
			isPalindro = false;
			break;
		}
	}

	// 都翻转
	for (int i = 0; i < index; ++i)
	{
		arr[index + i] = arr[index - 1 - i];
	}
	t1 = 0;
	for (int i = 2 * index - 1; i >= 0; --i)
	{
		t1 = t1 * 10 + arr[i];
	}

	// 以中间为轴
	for (int i = 0; i < index - 1; ++i)
	{
		arr[index + i] = arr[index - i - 2];
	}
	t2 = 0;
	for (int i = 2 * index - 2; i >= 0; --i)
	{
		t2 = t2 * 10 + arr[i];
	}
	return isPalindro;
}

bool IsPrime(int num)
{
	int sqrtNum = sqrt((double)num);
	for (int i = 2; i <= sqrtNum; ++i)
	{
		if (num % i == 0)
		{
			return false;
		}
	}
	return true;
}

bool IsPalindr(int num)
{
	return false;
}


void TestPrim(int tmp, int a, int b, set<int> &ans)
{
	if (tmp >= a && tmp <= b)
	{
		if (IsPrime(tmp))
		{
			//cout << tmp1 << endl;
			if (ans.find(tmp) == ans.end())
			{
				ans.insert(tmp);
			}
		}
	}
}

bool Prin2(int num, int &t1, int &t2)
{
	int index = 0;
	while (num)
	{
		arr[index++] = num % 10;
		num /= 10;
	}
	bool isPalindro = true;
	for (int i = 0; i < index / 2; ++i)
	{
		if (arr[i] != arr[index - 1 - i])
		{
			isPalindro = false;
			break;
		}
	}
	for (int i = 0; i < index; ++i)
	{
		arr[index + i] = arr[i];
	}

	// 都翻转
	for (int i = 0; i < index; ++i)
	{
		 arr[index - 1 - i] = arr[index + i];
	}
	t1 = 0;
	for (int i = 2 * index - 1; i >= 0; --i)
	{
		t1 = t1 * 10 + arr[i];
	}

	// 以中间为轴
	for (int i = 0; i < index; ++i)
	{
		arr[index - 1 + i] = arr[index + i];
	}

	for (int i = 0; i < index - 1; ++i)
	{
		arr[index - i - 2] = arr[index + i];
	}
	t2 = 0;
	for (int i = 2 * index - 2; i >= 0; --i)
	{
		t2 = t2 * 10 + arr[i];
	}
	return isPalindro;
}