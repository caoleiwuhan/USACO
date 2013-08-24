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

const int MAXV = 151;

// 位置
int pos[MAXV][2];

// 邻接矩阵
double dist[MAXV][MAXV];

double maxDist[MAXV];

int unionSet[MAXV];


////////////////////////////////////////////////////////////////////////////
// 并查集
int unionFather[MAXV];
 
int GetFatherUnion(int v)
{
    if (unionFather[v] == v)
	{
       return v;
	}
    return (unionFather[v] = GetFatherUnion(unionFather[v]));
}
 
bool Same(int x,int y)
{
     return (GetFatherUnion(x) == GetFatherUnion(y));
}

void Judge(int x,int y){
    int fx,fy;
    fx = GetFatherUnion(x);
    fy = GetFatherUnion(y);

    if (fx == fy) 
		return ;

    unionFather[fx] = fy;
}

void UnionInit(int N)
{
	for (int i = 0; i < N; ++i)
	{
		 unionFather[i] = i;
	}
}


////////////////////////////////////////////////////////////////////////////



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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/2.4.3 Cow Tours/input9.txt";
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
	int num;
	cin >> num;
	for (int i = 0; i < num; ++i)
	{
		cin >> pos[i][0] >> pos[i][1];
	}
	for (int i = 0; i < num; ++i)
	{
		for (int j = 0; j < num; ++j)
		{
			dist[i][j] = 0x7FFFFFFF;
		}
	}

	UnionInit(num);

	string str;
	cin.ignore();
	for (int i = 0; i < num; ++i)
	{
		getline(cin, str);
		for (int j = 0; j < num; ++j)
		{
			char ch = str[j];
			if (ch == '1')
			{
				double x = fabs(double(pos[i][0] - pos[j][0]));
				double y = fabs(double(pos[i][1] - pos[j][1]));
				double len = sqrt(x * x + y * y);
				dist[i][j] = len;
				dist[j][i] = len;

				Judge(i, j);
			}
		}
	}
	
	// 统计并查集的个数
	int count = 0;
	for (int i = 0; i < num; ++i)
	{
		bool exist = false;
		for (int j = 0; j < count; ++j)
		{
			if (GetFatherUnion(i) == unionSet[j])
			{
				exist = true;
				break;
			}
		}
		if (!exist)
		{
			unionSet[count++] = GetFatherUnion(i);
		}
	}

	double minDist = 0x7FFFFFFF;
	int start, to;
	for (int i = 0; i < num; ++i)
	{
		for (int j = 0; j < num; ++j)
		{
			if (!Same(i, j))
			{
				double x = fabs(double(pos[i][0] - pos[j][0]));
				double y = fabs(double(pos[i][1] - pos[j][1]));
				double len = sqrt(x * x + y * y);
				if (len < minDist)
				{
					minDist = len;
					start = i;
					to = j;
				}
			}
		}
	}

	dist[start][to] = minDist;
	dist[to][start] = minDist;

	// Floyd
	for (int k = 0; k < num; ++k)
	{
		for (int i = 0; i < num; ++i)
		{
			for (int j = 0; j < num; ++j)
			{
				if (i != j && i != k && j != k)
				{
					double cur = dist[i][j];
					if ((dist[i][k] != 0x7FFFFFFF) &&
						(dist[k][j] != 0x7FFFFFFF) &&
						(dist[i][k] + dist[k][j] < cur))
					{
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}
	}

	double maxLen = 0;
	for (int i = 0; i < num; ++i)
	{
		for (int j = 0; j < num; ++j)
		{
			if (i != j)
			{
				if (dist[i][j] > maxLen)
				{
					maxLen = dist[i][j];
				}
			}
		}
	}
	
	//double total = max1 + max2 + minDist;
	cout << fixed << setprecision(6) << maxLen << endl;
}

