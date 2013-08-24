#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <list>
#include <map>
#include <cstring>
#include <cctype>
#include <queue>
#include <cmath>
#include <limits>
#include <cfloat>
#include <iomanip>


using namespace std;

#define _MY_DEBUG_

const int MAXV = 252;

char matrix[MAXV][MAXV];

bool f[MAXV][MAXV][MAXV];

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/3.3.4 Home on the Range/input7.txt";
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
	memset(matrix, 0, sizeof(matrix));
	memset(f, 0, sizeof(f));
	int length;
	cin >> length;
	for (int i = 1; i <= length; ++i)
	{
		for (int j = 1; j <= length; ++j)
		{
			char tmp;
			cin >> tmp;
			matrix[i][j] = tmp;
			if (tmp == '1')
			{
				f[i][j][1] = true;
			}
		}
	}

	for (int k = 2; k <= length; ++k)
	{
		for (int i = 1; i <= length; ++i)
		{
			for (int j = 1; j <= length; ++j)
			{
				bool isOK = false;
				if (f[i][j][k-1])
				{				
					isOK = true;
					int rowMax = i + k - 1;
					int col = j + k - 1;
					for (int m = i; m <= rowMax; ++m)
					{
						if (matrix[m][col] != '1')
						{
							isOK = false;
							break;
						}
					}
					if (isOK)
					{
						int row = i + k - 1;
						int colMax = j + k - 1;
						for (int n = j; n <= colMax; ++n)
						{
							if (matrix[row][n] != '1')
							{
								isOK = false;
								break;
							}
						}
					}					
				}
				if (isOK)
				{
					f[i][j][k] = true;
				}
				else
				{
					f[i][j][k] = false;
				}
			}
		}
	}

	for (int k = 2; k <= length; ++k)
	{
		int count = 0;
		for (int i = 1; i <= length; ++i)
		{
			for (int j = 1; j <= length; ++j)
			{
				if (f[i][j][k])
				{
					++count;
				}
			}
		}
		if (count)
		{
			cout << k << ' ' << count << endl;
		}
	}

}

