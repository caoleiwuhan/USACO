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

struct Node
{
	int start;
	int end;
	Node() {}

	Node(int _start, int _end) : start(_start), end(_end) {}
};


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

const int WHEEL_NUM = 5;

// 每个轮子的角度
int angle[WHEEL_NUM];

int speed[WHEEL_NUM];

// 窟窿的数目
int wNum[WHEEL_NUM];

// 窟窿的范围
Node wRange[WHEEL_NUM][WHEEL_NUM + 1];


bool rMap[361];
bool tmpMap[361];

bool Cmp(Node &left, Node &right)
{
	if (left.start < right.start)
	{
		return true;
	}
	return false;
}


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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/3.2.3 Spinning Wheels/input.txt";
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
	for (int i = 0; i < WHEEL_NUM; ++i)
	{
		int num;
		cin >> speed[i] >> num;
		wNum[i] = num;
		int start, end;
		for (int j = 0; j < wNum[i]; ++j)
		{
			cin >> start >> end;
			wRange[i][j].start = start;
			wRange[i][j].end = end;		
		}
	}

	//for (int i = 0; i < WHEEL_NUM; ++i)
	//{
	//	sort(wRange[i], wRange[i] + wNum[i], Cmp);
	//}

	for (int i = 0; ; ++i)
	{
		memset(rMap, 1, sizeof(rMap));
			
		for (int j = 0; j < WHEEL_NUM; ++j)
		{
			int nAngle = (speed[j] * i) % 360;
			angle[j] = nAngle;
			memset(tmpMap, 0, sizeof(tmpMap));
			for (int k = 0; k < wNum[j]; ++k)
			{
				int start = (wRange[j][k].start + nAngle) % 360;
				int end = (wRange[j][k].end + nAngle) % 360;
				if (start <= end)
				{
					memset(tmpMap + start, 1, (end - start + 1));
				}
				else
				{
					memset(tmpMap + start, 1, 360 - start);
					memset(tmpMap, 1, end + 1);
				}
			}
			for (int s = 0; s < 360; ++s)
			{
				rMap[s] = rMap[s] & tmpMap[s];
			}
		}
		for (int s = 0; s < 360; ++s)
		{
			if (rMap[s])
			{
				cout << i << endl;
				return;
			}
		}
	}
}


