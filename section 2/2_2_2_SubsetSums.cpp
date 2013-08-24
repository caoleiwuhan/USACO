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

const int MAXV = 40;

unsigned f[MAXV][MAXV * (MAXV + 1) / 2];

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/2.2.2 Subset Sums/input6.txt";
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

/*
	背包：前i个放入后，重量为j。。。
	放或者不放
*/
void Process()
{
	int N;
	cin >> N;
	int multi = N * (N + 1) / 2;
	if (multi & 1)
	{
		cout << 0 << endl;
		return;
	}
	multi >>= 1;

	f[1][1] = 1;
	f[1][0] = 1;
	for (int i = 2; i <= N; ++i)
	{
		for (int j = 0; j <= multi; ++j)
		{
			if (j >= i)
			{
				f[i][j] = f[i-1][j] + f[i-1][j-i];
			}
			else
			{
				f[i][j] = f[i-1][j];
			}
		}
	}

	cout << f[N][multi] / 2 << endl;
}

