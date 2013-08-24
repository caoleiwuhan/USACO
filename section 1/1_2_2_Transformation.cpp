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

const int MAXV = 11;
// 起始图像
char initTile[MAXV][MAXV];

// 目标图像
char resultTile[MAXV][MAXV];

// 中间图像
char middleTile[MAXV][MAXV];


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();


/*
	1：将起始图像顺时针90度翻转
*/
bool Transform1(char start[][MAXV], char to[][MAXV], int num);

/*
	2：将起始图像顺时针180度翻转
*/
bool Transform2(char start[][MAXV], char to[][MAXV], int num);

/*
	3：将起始图像顺时针270度翻转
*/
bool Transform3(char start[][MAXV], char to[][MAXV], int num);

/*
	4：镜像
*/
bool Transform4(char start[][MAXV], char to[][MAXV], int num);

/*
	5：镜像
*/
bool Transform5(char start[][MAXV], char to[][MAXV], int num);


/*
	判断俩个矩阵是否相同
*/
bool IsTwoImageEqual(char start[][MAXV], char to[][MAXV], int num);

/*
	打印：方便调试
*/
void PrintImage(char start[][MAXV], int num);


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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/1.2.2 Transformations/input8.txt";
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
	int num = 0;
	cin >> num;
	// 记录@个数，如果两者@不一样，则一定不能成功
	int startCount = 0;
	int toCount = 0;
	char ch;
	// 读入起始图像
	for (int i = 1; i <= num; ++i)
	{
		for (int j = 1; j <= num; ++j)
		{
			cin >> ch;
			initTile[i][j] = ch;
			if (ch == '@')
			{
				++startCount;
			}
		}
	}
	// 读入目标图像
	for (int i = 1; i <= num; ++i)
	{
		for (int j = 1; j <= num; ++j)
		{
			cin >> ch;
			resultTile[i][j] = ch;
			if (ch == '@')
			{
				++toCount;
			}
		}
	}
	if (startCount != toCount)
	{
		cout << 7 << endl;
		return;
	}
	if (Transform1(initTile, middleTile, num))
	{
		cout << 1 << endl;
		return;
	}
	if (Transform2(initTile, middleTile, num))
	{
		cout << 2 << endl;
		return;
	}
	if (Transform3(initTile, middleTile, num))
	{
		cout << 3 << endl;
		return;
	}
	if (Transform4(initTile, middleTile, num))
	{
		cout << 4 << endl;
		return;
	}
	if (Transform5(initTile, middleTile, num))
	{
		cout << 5 << endl;
		return;
	}
	if (IsTwoImageEqual(initTile, resultTile, num))
	{
		cout << 6 << endl;
		return;
	}

	cout << 7 << endl;

}


/*
	1：将起始图像顺时针90度翻转
*/
bool Transform1(char start[][MAXV], char to[][MAXV], int num)
{

//PrintImage(start, num);
	for (int i = 1; i <= num; ++i)
	{
		for (int j = 1; j <= num; ++j)
		{
			to[j][num + 1 - i] = start[i][j];
		}
	}
//PrintImage(to, num);

	if (IsTwoImageEqual(to, resultTile, num))
	{
		return true;
	}
	return false;
}

bool Transform2(char start[][MAXV], char to[][MAXV], int num)
{

//PrintImage(start, num);
	// 临时矩阵
	char tmpTile[MAXV][MAXV];	
	memcpy(tmpTile, start, MAXV * MAXV);
//PrintImage(tmpTile, num);
	// 顺时针旋转90
	Transform1(tmpTile, to, num);
	Transform1(to, tmpTile, num);
	// 将结果拷贝到middleTile中
	memcpy(to, tmpTile, MAXV * MAXV);

//PrintImage(to, num);
	if (IsTwoImageEqual(to, resultTile, num))
	{
		return true;
	}
	return false;
}

bool Transform3(char start[][MAXV], char to[][MAXV], int num)
{
//PrintImage(start, num);

	// 临时矩阵
	char tmpTile[MAXV][MAXV];
	memcpy(tmpTile, start, MAXV * MAXV);
	// 顺时针旋转90
	Transform1(tmpTile, to, num);
	Transform1(to, tmpTile, num);
	Transform1(tmpTile, to, num);

//PrintImage(to, num);
	if (IsTwoImageEqual(to, resultTile, num))
	{
		return true;
	}
	return false;
	
}

bool Transform4(char start[][MAXV], char to[][MAXV], int num)
{
//PrintImage(start, num);

	memcpy(to, start, MAXV * MAXV);

	int middle = num / 2;
	for (int j = 1; j <= middle; ++j)
	{
		for (int i = 1; i <= num; ++i)
		{			
			to[i][j] = start[i][num + 1 - j];
			to[i][num + 1 - j] = start[i][j];
		}
	}

//PrintImage(to, num);

	if (IsTwoImageEqual(to, resultTile, num))
	{
		return true;
	}
	return false;
}

/*
	5：镜像
*/
bool Transform5(char start[][MAXV], char to[][MAXV], int num)
{
	// 临时矩阵
	char tmpTile[MAXV][MAXV];
	// 镜像
	Transform4(start, tmpTile, num);

	Transform1(tmpTile, to, num);
	if (IsTwoImageEqual(to, resultTile, num))
	{
		return true;
	}
	
	Transform2(tmpTile, to, num);
	if (IsTwoImageEqual(to, resultTile, num))
	{
		return true;
	}

	Transform3(tmpTile, to, num);
	if (IsTwoImageEqual(to, resultTile, num))
	{
		return true;
	}

	return false;
}

bool IsTwoImageEqual(char start[][MAXV], char to[][MAXV], int num)
{
	for (int i = 1; i <= num; ++i)
	{
		for (int j = 1; j <= num; ++j)
		{			
			if (start[i][j] != to[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

void PrintImage(char start[][MAXV], int num)
{
	for (int i = 1; i <= num; ++i)
	{
		for (int j = 1; j <= num; ++j)
		{			
			cout << start[i][j];
		}
		cout << endl;
	}
	cout << "----------------------------------" << endl;
}