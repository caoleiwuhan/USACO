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

// 硬币数
const int MAXV = 26;
// 硬币种类
int coins[MAXV];

int s[10001][MAXV];

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/2.2.4 Money Systems/input2.txt";
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
	int V, N;
	cin >> V >> N;
	coins[0] = 0;
	for (int i = 1; i <= V; ++i)
	{
		cin >> coins[i];
	}
	sort(coins, coins + V + 1);
	for (int i = 1; i <= N; ++i)
	{
		if (i % coins[1] == 0)
		{
			s[i][1] = 1;
		}
	}
	

	// 钱数为i，最大面值为coins[j]的个数
	for (int i = coins[1] + 1; i <= N; ++i)
	{
		for (int j = 2; (j <= V) && (i >= coins[j]); ++j)
		{
			int num = coins[j];
			int kind = 0;

			for (int k = 1; k * num < i; ++k)
			{
				for (int t = j - 1; t > 0; --t)
				{
					kind += s[i-k*num][t];
				}					
			}
			if (i % coins[j] == 0)
			{
				kind += 1;
			}
			s[i][j] = kind;
		}
	}
	int ans = 0;
	for (int i = 1; i <= V; ++i)
	{
		ans += s[N][i];
		//cout << s[N][i] << endl;
	}
	cout << ans << endl;
}