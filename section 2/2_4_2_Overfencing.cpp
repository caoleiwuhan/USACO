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

const int MAXW = 39;
const int MAXH = 100;

bool fenceMap[MAXH][MAXW][4];

int length1[MAXH][MAXW];

int length2[MAXH][MAXW];

bool used[MAXH][MAXW];

int dirMap[4][2] = 
{
	-1, 0,
	0, 1,
	1, 0,
	0, -1
};

struct Node
{
	int x;
	int y;
	int length;
	Node(int _x, int _y, int _length):
	x(_x), y(_y), length(_length)
	{}

};

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

void BFS(int lenthMap[][MAXW], int row, int col, int startx, int starty);

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/2.4.2 Overfencing/input10.txt";
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
	int W, H;
	cin >> W >> H;
	
	int row = 2 * H + 1;
	int col = 2 * W + 1;
	// 两个出口
	int x1 = -1;
	int y1 = -1;
	// 方向：0、1、2、3
	int z1 = -1;

	int x2 = -1;
	int y2 = -1;
	int z2 = -1;

	string str;
	cin.ignore();
	for (int i = 0; i < row; ++i)
	{
		getline(cin, str);
		//cin.ignore();
		char ch;
		for (int j = 0; j < col; ++j)
		{
			ch = str[j];
			// 奇数行
			if (i & 1)
			{
				if (!(j & 1))
				{ // 只处理j为偶数的情况
					if (j == 0 || (j == col - 1))
					{
						if (j == 0)
						{
							if (ch == ' ')
							{
								fenceMap[i / 2][0][3] = true;
								if (x1 == -1)
								{
									x1 = i / 2;
									y1 = 0;
									z1 = 3;
								}
								else
								{
									x2 = i / 2;
									y2 = 0;
									z2 = 3;
								}
							}
						}
						else
						{
							if (ch == ' ')
							{
								fenceMap[i / 2][j / 2 - 1][1] = true;
								if (x1 == -1)
								{
									x1 = i / 2;
									y1 = j / 2 - 1;
									z1 = 1;
								}
								else
								{
									x2 = i / 2;
									y2 = j / 2 - 1;
									z2 = 1;
								}
							}
						}
					}
					else
					{
						if (ch == ' ')
						{// 当前的上面、上一个的下面：只有两种可能
							fenceMap[i / 2][j / 2][3] = true;
							fenceMap[i / 2][j / 2 - 1][1] = true;
						}
					}
				}
			}
			else
			{// 偶数行：只处理j为奇数的情况
				if (j & 1)
				{
					// 第一行、最后一行
					if (i == 0 || (i == row - 1))
					{
						if (i == 0)
						{ // 第0行上部
							if (ch == ' ')
							{
								fenceMap[i / 2][j / 2][0] = true;
								if (x1 == -1)
								{
									x1 = 0;
									y1 = j / 2;
									z1 = 0;
								}
								else
								{
									x2 = 0;
									y2 = j / 2;
									z2 = 0;
								}
							}
						}
						else
						{// 最后一行下部
							if (ch == ' ')
							{
								fenceMap[i / 2 - 1][j / 2][2] = true;
								if (x1 == -1)
								{
									x1 = i / 2 - 1;
									y1 = j / 2;
									z1 = 2;
								}
								else
								{
									x2 = i / 2 - 1;
									y2 = j / 2;
									z2 = 2;
								}
							}
						}
					}
					else
					{
						if (ch == ' ')
						{// 当前的上面、上一个的下面：只有两种可能
							fenceMap[i / 2][j / 2][0] = true;
							fenceMap[i / 2 - 1][j / 2][2] = true;
						}
					}				

				}

			}
			
		}
	}
	BFS(length1, H, W, x1, y1);
	BFS(length2, H, W, x2, y2);

	int maxLen = 0;
	for (int i = 0; i < H; ++i)
	{
		for (int j = 0; j < W; ++j)
		{
			// 两者中的最小
			int cur = 0x7FFFFFFF;
			if (length1[i][j] != 0)
			{
				cur = length1[i][j];
			}
			 
			if (length2[i][j] && (cur > length2[i][j]))
			{
				cur = length2[i][j];
			}
			if (cur > maxLen)
			{
				maxLen = cur;
			}
		}
	}
	cout << maxLen << endl;
}

void BFS(int lengthMap[][MAXW], int row, int col, int startx, int starty)
{
	memset(used, 0, sizeof(used));
	// 边界

	Node *n = new Node(startx, starty, 1);
	used[startx][starty] = true;

	lengthMap[startx][starty] = 1;
	queue<Node *> q;
	q.push(n);

	while (!q.empty())
	{
		Node *curNode = q.front();
		q.pop();
		int x = curNode->x;
		int y = curNode->y;
		for (int i = 0; i < 4; ++i)
		{
			if (fenceMap[x][y][i])
			{
				int newx = x + dirMap[i][0];
				int newy = y + dirMap[i][1];
				if ((newx >= 0 && newx < row) && 
					(newy >= 0 && newy < col) && 
					!used[newx][newy])				
				{
					Node *nextNode = new Node(newx, newy, curNode->length + 1);
					used[newx][newy] = true;
					lengthMap[newx][newy] = curNode->length + 1;

					q.push(nextNode);

				}
			}
		}
	}
}