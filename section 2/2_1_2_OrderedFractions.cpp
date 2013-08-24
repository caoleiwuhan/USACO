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

struct Frac
{
	int numerator;
	int denomirator;

	bool operator == (const Frac & f) const
	{
		if (f.numerator == numerator && f.denomirator == denomirator)
		{
			return true;
		}
		return false;
	}

	bool operator < (const Frac & f) const
	{
		int n1 = numerator * f.denomirator;
		int n2 = f.numerator * denomirator;
		if (n1 < n2)
		{
			return true;
		}
		return false;
	}
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
	最大公约数
*/
int gcd(int a, int b);

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/2.1.2 Ordered Fractions/input11.txt";
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
	int N;
	cin >> N;

	set<Frac> fracs;
	Frac frac;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j < i; ++j)
		{
			int divisor = gcd(j, i);
			frac.numerator = j / divisor;
			frac.denomirator = i / divisor;
			// 如果没有，这加入
			if (fracs.find(frac) == fracs.end())
			{
				fracs.insert(frac);
			}
		}
	}
	cout << "0/1" << endl;
	for (set<Frac>::iterator itr = fracs.begin(); itr != fracs.end(); ++itr)
	{
		cout << itr->numerator << '/' << itr->denomirator << endl;
	}
	cout << "1/1" << endl;

}

int gcd(int a, int b)
{
	if (b == 0)
	{
		return a;
	}
	return gcd(b, a % b);
}