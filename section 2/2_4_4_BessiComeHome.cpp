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

// 前面26是大写，后面26是小写
const int MAXV = 52;

int dist[MAXV][MAXV];

int ans[MAXV][MAXV];

bool exist[MAXV];

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/2.4.4 Bessie Come Home/input7.txt";
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
	int count = 0;
	cin >> count;
	char a, b;
	int len;
	int gap = 'a' - 'A';
	for (int i = 0; i < MAXV; ++i)
	{
		for (int j = 0; j < MAXV; ++j)
		{
			dist[i][j] = 0x7FFFFFFF;
			//ans[i][j] = 0x7FFFFFFF;
		}
	}

	for (int i = 0; i < count; ++i)
	{
		cin >> a >> b >> len;
		// 
		int index1;
		int index2;
		if (a >= 'A' && a <= 'Z')
		{
			index1 = a - 'A';
			exist[index1] = true;
		}
		else
		{
			index1 = a - 'a' + 26;
		}
		if (b >= 'A' && b <= 'Z')
		{
			index2 = b - 'A';
			exist[index2] = true;
		}
		else
		{
			index2 = b - 'a' + 26;
		}
		if (len < dist[index1][index2])
		{
			dist[index1][index2] = len;
			dist[index2][index1] = len;
		}
	}

	// Floyd算法
	for (int k = 0; k < MAXV; ++k)
	{
		for (int i = 0; i < MAXV; ++i)
		{
			if (i != k)
			{
				for (int j = 0; j < MAXV; ++j)
				{
					if ((k != j) && (i != j))
					{
						int cur = dist[i][j];
						if ((dist[i][k] != 0x7FFFFFFF) &&
							(dist[k][j] != 0x7FFFFFFF) &&
							(dist[i][k] + dist[k][j] < cur))
						{
							cur = dist[i][k] + dist[k][j];
						}
						dist[i][j] = cur;
					}
				}
			}
		}
	}
	int minLen = 0x7FFFFFFF;
	char resChar = ' ';
	for (int i = 0; i < 26; ++i)
	{
		if (i != 25)
		{
			if ((dist[25][i] < minLen) && exist[i])
			{
				minLen = dist[25][i];
				resChar = char('A' + i);
			}
		}
	}
	cout << resChar << ' ' << minLen << endl;
}

