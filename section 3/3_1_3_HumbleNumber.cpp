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

const int PRIME_NUM = 101;
const int MAXV = 100001;

unsigned prime[PRIME_NUM];

unsigned pointer[PRIME_NUM];

unsigned numbers[MAXV];

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/3.1.3 Humble Numbers/input8.txt";
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
	unsigned K, N;
	cin >> K >> N;

	prime[0] = 1;
	for (unsigned i = 1; i <= K; ++i)
	{
		cin >> prime[i];
	}
	sort(prime, prime + K);

	for (unsigned i = 1; i <= K; ++i)
	{
		// 每一个都从0开始计算
		pointer[i] = 0;
	}
	// 第0个
	numbers[0] = 1;

	for (unsigned i = 1; i <= N; ++i)
	{
		unsigned minPointer = 0x7FFFFFFF;
		unsigned index = 0;
		unsigned curMax = numbers[i - 1];
		for (unsigned j = 1; j <= K; ++j)
		{
			unsigned tmp = numbers[pointer[j]] * prime[j];
			// 找到第一个比curMax大的数
			while (tmp <= curMax)
			{				
				tmp = numbers[++pointer[j]] * prime[j];
			}
			if (tmp < minPointer)
			{
				minPointer = tmp;
				index = j;
			}
		}
		numbers[i] = minPointer;
	}
	cout << numbers[N] << endl;
}

