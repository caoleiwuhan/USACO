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
#include <limits>
#include <cfloat>
#include <iomanip>


using namespace std;

#define _MY_DEBUG_

const int MAX_STAMP = 51;

const int MAXV = 2000001;

int stamps[MAX_STAMP];

int s[MAXV];

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/3.1.6 Stamps/input12.txt";
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
	int K, N;
	cin >> K >> N;

	for (int i = 0; i < N; ++i)
	{
		cin >> stamps[i];
	}
	for (int i = 0; i < N; ++i)
	{
		s[stamps[i]] = 1;
	}

	sort(stamps, stamps + N);
	if (stamps[0] != 1)
	{
		cout << 0 << endl;
		return;
	}

	for (int i = 2; i < MAXV; ++i)
	{
		if (s[i])
		{
			continue;
		}

		int curMin = 0x7FFFFFFF;
		bool isOK = false;
		
		for (int j = 0; j < N; ++j)
		{
			if (stamps[j] > i)
			{
				break;
			}
			int curCount = s[i - stamps[j]];
			if (curCount != 0)
			{
				++curCount;
				if (curCount <= K)
				{
					if (curCount < curMin)
					{
						curMin = curCount;
						isOK = true;
					}
				}
			}
		}
		if (isOK)
		{
			s[i] = curMin;
		}
		else
		{
			cout << (i - 1) << endl;
			break;
		}
	}
}

