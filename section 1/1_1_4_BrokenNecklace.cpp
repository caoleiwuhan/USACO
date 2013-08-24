#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define _MY_DEBUG_

// 项链最大350个
const int MAXV = 351;

char necklace[MAXV];


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();



int main()
{
	MainStructure();
	return 0;
}

void MainStructure()
{
	
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/1.1.4 Broken Necklace/necklace.in7";
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
	int neckNum = 0;
	cin >> neckNum;
	for (int i = 0; i < neckNum; ++i)
	{
		cin >> necklace[i];
	}
	int maxNum = 0;

	// 从中间断开：断开位置为(i, i+1)
	for (int i = 0; i < neckNum; ++i)
	{
		int curMax = 2;

		// 从i向前数
		// 如果一开始就是白色的
		bool isStartWhite = false;
		char ch1 = necklace[i];
		if (ch1 == 'w')
		{
			isStartWhite = true;
		}

		for (int j = i - 1; ; --j)
		{
			j = (j + neckNum) % neckNum;
			if (j == i)
			{
				break;
			}

			if (isStartWhite)
			{
				ch1 = necklace[j];
				if (ch1 != 'w')
				{
					isStartWhite = false;
				}
			}
			if (necklace[j] == ch1 || necklace[j] == 'w')
			{
				++curMax;
			}
			else
			{
				break;
			}
		}
		if (curMax >= neckNum)
		{
			maxNum = neckNum;
			break;
		}

		// 从i+1向后数
		isStartWhite = false;
		char ch2 = necklace[(i + 1) % neckNum];
		if (ch2 == 'w')
		{
			isStartWhite = true;
		}
		for (int j = i + 2; ; ++j)
		{
			j = j % neckNum;
			if (j == i + 1)
			{
				break;
			}
			if (isStartWhite)
			{
				ch2 = necklace[j];
				if (ch2 != 'w')
				{
					isStartWhite = false;
				}
			}
			if (necklace[j] == ch2 || necklace[j] == 'w')
			{
				++curMax;
			}
			else
			{
				break;
			}
		}
		if (curMax >= neckNum)
		{
			maxNum = neckNum;
			break;
		}
		if (curMax > maxNum)
		{
			maxNum = curMax;
		}
	}
	cout << maxNum << endl;
}


