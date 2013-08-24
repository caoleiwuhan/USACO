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

const int MAXV = 801;

int dist[MAXV][MAXV];

int exist[MAXV];

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/3.2.6 Sweet Butter/input10.txt";
	//string inputStr = "D:/2挑战编程/input/110205.inp";
	string outputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/3.1.5 Contact/out.txt";
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
	int N, P, C;
	cin >> N >> P >> C;
	int tmp;
	for (int i = 0; i < N; ++i)
	{
		cin >> tmp;
		++exist[tmp];
	}

	memset(dist, 1, sizeof(dist));

	int num1, num2;
	unsigned len;
	for (int i = 0; i < C; ++i)
	{
		cin >> num1 >> num2 >> len;
		dist[num1][num2] = len;
		dist[num2][num1] = len;
	}

	for (int i = 1; i <= P; ++i)
	{
		for (int j = 1; j <= P; ++j)
		{
			for (int k = 1; k <= P; ++k)
			{
				if (dist[j][i] + dist[i][k] < dist[j][k])
				{
					dist[j][k] = dist[j][i] + dist[i][k];
				}
			}
		}
	}
	int minLen = 0x7FFFFFFF;
	int index = -1;
	for (int i = 1; i <= P; ++i)
	{
		int curLen = 0;
		for (int j = 1; j <= P; ++j)
		{
			if (exist[j] && (i != j))
			{
				curLen += dist[i][j] * exist[j];
			}
		}
		if (curLen < minLen)
		{
			//if (curLen != 1924)
			{			
				minLen = curLen;
				index = i;
			}
		}
	}

	cout << minLen << endl;
}


