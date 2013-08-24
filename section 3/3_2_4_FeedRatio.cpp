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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/3.2.4 Feed Ratios/input6.txt";
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
	int a, b, c;
	cin >> a >> b >> c;
	int a1, b1, c1;
	cin >> a1 >> b1 >> c1;
	int a2, b2, c2;
	cin >> a2 >> b2 >> c2;
	int a3, b3, c3;
	cin >> a3 >> b3 >> c3;

	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			for (int k = 0; k < 100; ++k)
			{
				if (i == 0 && j == 0 && k == 0)
				{
					continue;
				}

				int ta = i * a1 + j * a2 + k * a3;
				int tb = i * b1 + j * b2 + k * b3;
				int tc = i * c1 + j * c2 + k * c3;
				if (ta < a ||
					tb < b ||
					tc < c)
				{
					continue;
				}

				if ((ta * b == tb * a) &&
					(ta * c == tc * a) &&
					(tb * c == tc * b))
				{
					int tmp = 0;
					if (a != 0)
					{
						tmp = ta / a;
					}
					else if (b != 0)
					{
						tmp = tb / b;
					}
					else
					{
						tmp = tc / c;
					}
					cout << i << ' ' << j << ' ' << k << ' ' << tmp << endl;
					return;
				}
			}
		}
	}
	cout << "NONE" << endl;

}


