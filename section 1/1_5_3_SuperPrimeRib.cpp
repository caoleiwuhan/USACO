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


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

bool IsPrime(int num);

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/1.5.3 Superprime Rib/input1.txt";
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
	int len = N;

	int start = 1;
	int end = 10;
	--N;
	while (N)
	{
		start *= 10;
		end *= 10;
		--N;
	}
	
	int from = start * 2;
	int to = start * 8;

	for (int i = from + 1; i < to; i += 2)
	{		
		int expand = start / 10;
		bool isOK = true;
		for (int j = 1; j < len; ++j)
		{
			int cur = i / expand;
			if (!IsPrime(cur))
			{
				isOK = false;
				break;
			}
			expand /= 10;
		}

		if (isOK)
		{
			cout << i << endl;
		}
	}
}


bool IsPrime(int num)
{
	if (num == 1)
	{
		return false;
	}
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