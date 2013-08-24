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

//#define _MY_DEBUG_

//#define SetBit2(i, j) \
//	(matrix[i * MAXV + j] &= (1 << (j % 8)))
//
//#define GetBit(i, j) \
//	(((matrix[i / 8][j / 8] & (1 << (j % 8))) >> (j % 8)))




const int MAXV = 252;
const int RANGE = MAXV / 8 + 1;

//char matrix[MAXV / 8 + 1][MAXV / 8 + 1];
//char f[MAXV / 8 + 1][MAXV / 8 + 1][MAXV / 8 + 1];
char matrix[MAXV * MAXV];
char f[MAXV * MAXV * MAXV];



inline void SetBit2(int i, int j)
{
	int index = i * MAXV + j;
	matrix[index / 8] |= (1 << (index % 8));
}

inline int GetBit2(int i, int j)
{
	int index = i * MAXV + j;
	return ((matrix[index / 8] & (1 << (index % 8))) >> (index % 8));
}

inline void SetBit3(int i, int j, int k)
{
	int index = i * MAXV * MAXV + j * MAXV + k;
	f[index / 8] |= (1 << (index % 8));
}

inline int GetBit3(int i, int j, int k)
{
	int index = i * MAXV * MAXV + j * MAXV + k;
	return ((f[index / 8] & (1 << (index % 8))) >> (index % 8));
}

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

void TestBit()
{
	SetBit2(1, 1);

	SetBit2(2, 7);

	SetBit2(2, 5);

	SetBit2(2, 8);

	cout << GetBit2(1, 1) << endl;
	cout << GetBit2(2, 7) << endl;
	cout << GetBit2(2, 8) << endl;
	cout << GetBit2(3, 1) << endl;

	SetBit3(1, 1, 1);

	SetBit3(2, 7, 1);

	SetBit3(2, 5, 1);

	SetBit3(2, 8, 1);

	cout << GetBit3(1, 1, 1) << endl;
	cout << GetBit3(2, 7, 1) << endl;
	cout << GetBit3(2, 8, 1) << endl;
	cout << GetBit3(3, 1, 1) << endl;
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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/3.3.4 Home on the Range/input6.txt";
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
	//TestBit();

}


void Process()
{	
	ifstream fin("range.in");
    ofstream fout("range.out");

	memset(matrix, 0, sizeof(matrix));
	memset(f, 0, sizeof(f));
	int length;
	fin >> length;
	for (int i = 1; i <= length; ++i)
	{
		for (int j = 1; j <= length; ++j)
		{
			char tmp;
			fin >> tmp;
			//matrix[i][j] = tmp;

			if (tmp == '1')
			{
				SetBit2(i, j);
				SetBit3(i, j, 1);
				//f[i][j][1] = true;
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
				//if (f[i][j][k-1])
				if (GetBit3(i, j, k-1))
				{				
					isOK = true;
					int rowMax = i + k - 1;
					int col = j + k - 1;
					for (int m = i; m <= rowMax; ++m)
					{
						//if (matrix[m][col] != '1')
						if (!GetBit2(m, col))
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
							//if (matrix[row][n] != '1')
							if (!GetBit2(row, n))
							{
								isOK = false;
								break;
							}
						}
					}					
				}
				if (isOK)
				{
					//f[i][j][k] = true;
					SetBit3(i, j, k);
				}
				/*else
				{
					f[i][j][k] = false;
				}*/
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
				//if (f[i][j][k])
				if (GetBit3(i, j, k))
				{
					++count;
				}
			}
		}
		if (count)
		{
			fout << k << ' ' << count << endl;
		}
	}

}

