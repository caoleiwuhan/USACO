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

using namespace std;

#define _MY_DEBUG_

// cow最大数
const int MAXV = 201;

// 保存
int cow[MAXV];

struct Inter
{
	int len;
	int from;
	int to;
};

Inter middle[MAXV];



/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

bool Cmp(const Inter& n1, const Inter& n2);


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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/1.3.2 Barn Repair/barn1.in10";
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
	int m;
	int s;
	int c;
	cin >> m >> s >> c;
	for (int i = 0; i < c; ++i)
	{
		cin >> cow[i];
	}
	// 对cow排序
	sort(cow, cow + c);
	for (int i = 0; i < c - 1; ++i)
	{
		middle[i].len = cow[i+1] - cow[i] - 1;
		middle[i].from = cow[i];
		middle[i].to = cow[i+1];
	}
	// 排序
	sort(middle, middle + c - 1, Cmp);
	int minus = 0;
	minus += (cow[0] - 1);
	minus += (s - cow[c - 1]);
	for (int i = 0; i < m - 1; ++i)
	{
		minus += middle[i].len;
	}
	
	cout << (s - minus) << endl;

}

bool Cmp(const Inter& n1, const Inter& n2)
{
	if (n1.len > n2.len)
	{
		return true;
	}
	else
	{
		return false;
	}
}