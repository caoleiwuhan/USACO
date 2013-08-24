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

const int MAXV = 501;

int disjoint[MAXV][MAXV];

int degree[MAXV];

vector<int> ans;

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

void DFS(int start, int nodeNum);



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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/3.3.1 Riding the Fences/input8.txt";
	//string inputStr = "D:/2挑战编程/input/110205.inp";
	string outputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/3.3.1 Riding the Fences/1.txt";
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
	int nodeNum = 0;
	int edgeNum;
	cin >> edgeNum;
	int n1, n2;
	for (int i = 0; i < edgeNum; ++i)
	{
		cin >> n1 >> n2;
		++disjoint[n1][n2];
		++disjoint[n2][n1];
		++degree[n1];
		++degree[n2];
		if (n1 > nodeNum)
		{
			nodeNum = n1;
		}
		if (n2 > nodeNum)
		{
			nodeNum = n2;
		}
	}
	// 找到一个度为奇数的点，开始遍历
	int start = 1;
	for (int i = 1; i <= nodeNum; ++i)
	{
		if (degree[i] & 1)
		{
			start = i;
			break;
		}
	}

	DFS(start, nodeNum);
	int size = ans.size();
	for (int i = ans.size() - 1; i >= 0; --i)
	{
		cout << ans[i] << endl;	
	}	
}

void DFS(int start, int nodeNum)
{
	if (degree[start] == 0)
	{
		ans.push_back(start);
		return;
	}
	for (int i = 1; i <= nodeNum; ++i)
	{
		if (disjoint[start][i])
		{
			while (disjoint[start][i])
			{
				--disjoint[start][i];
				--disjoint[i][start];
				--degree[start];
				--degree[i];
				DFS(i, nodeNum);
			}
		}
	}
	ans.push_back(start);
}