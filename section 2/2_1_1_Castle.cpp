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

const int MAXV = 51;

int rooms[MAXV][MAXV];

int numbers[MAXV][MAXV];

int roomMaps[MAXV * MAXV];


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

void DFS(int row, int col, int curRow, int curCol, int total);

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/2.1.1 The Castle/input8.txt";
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
	int col, row;
	cin >> col >> row;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			cin >> rooms[i][j];
		}
	}
	int total = 0;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if (!numbers[i][j])
			{
				DFS(row, col, i, j, ++total);
			}
		}
	}

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			++roomMaps[numbers[i][j]];
		}
	}

	int maxCount = 0;
	for (int i = 1; i <= total; ++i)
	{
		if (roomMaps[i] > maxCount)
		{
			maxCount = roomMaps[i];
		}
	}

	int maxRoom = 0;
	int maxRow = 0;
	int maxCol = 0;
	int direction = 0;
		
	for (int j = 0; j < col; ++j)
	{
		for (int i = row - 1; i >= 0; --i)
		{
			// 向上
			if (i != 0)
			{
				if (numbers[i][j] != numbers[i-1][j])
				{
					int tmp = roomMaps[numbers[i][j]] + roomMaps[numbers[i-1][j]];
					if (tmp > maxRoom)
					{
						maxRoom = tmp;
						maxRow = i;
						maxCol = j;
						direction = 0;
					}
				}
			}
			// 向右
			if (j != col - 1)
			{
				if (numbers[i][j] != numbers[i][j+1])
				{
					int tmp = roomMaps[numbers[i][j]] + roomMaps[numbers[i][j+1]];
					if (tmp > maxRoom)
					{
						maxRoom = tmp;
						maxRow = i;
						maxCol = j;
						direction = 1;
					}
				}
			}
		}
	}
	
	cout << total << endl;
	cout << maxCount << endl;
	cout << maxRoom << endl;
	cout << (maxRow + 1) << ' ' << (maxCol + 1) << ' ';
	if (direction == 0)
	{
		cout << 'N' << endl;
	}
	else
	{
		cout << 'E' << endl;
	}
}

void DFS(int row, int col, int curRow, int curCol, int total)
{
	numbers[curRow][curCol] = total;
	// 判断四个方向是否可行
	// 上方可以，并且上方没有被遍历过
	if ((curRow != 0) && !(rooms[curRow][curCol] & 2) && !numbers[curRow-1][curCol])
	{
		numbers[curRow-1][curCol] = total;
		DFS(row, col, curRow-1, curCol, total);
	}
	// 下方可以
	if ((curRow != row - 1) && !(rooms[curRow][curCol] & 8) && !numbers[curRow+1][curCol])
	{
		numbers[curRow+1][curCol] = total;
		DFS(row, col, curRow+1, curCol, total);
	}
	// 左方可以
	if ((curCol != 0) && !(rooms[curRow][curCol] & 1) && !numbers[curRow][curCol-1])
	{
		numbers[curRow][curCol-1] = total;
		DFS(row, col, curRow, curCol-1, total);
	}
	// 右方可以
	if ((curCol != col - 1) && !(rooms[curRow][curCol] & 4) && !numbers[curRow][curCol+1])
	{
		numbers[curRow][curCol+1] = total;
		DFS(row, col, curRow, curCol+1, total);
	}
}