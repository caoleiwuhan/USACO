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

const int KIND_NUM = 6;
const int CUT_NUM = 101;

struct CutOff
{
	int index;	// 商品编号
	int count;	// 数量
};

struct Product
{
	int index;
	int count;
	int price;
};

// 优惠组合
CutOff kind[CUT_NUM][KIND_NUM];
// 每一种优惠的商品种类的个数
int cutNum[CUT_NUM];
// 每一种优惠的价格
int cutPrice[CUT_NUM];
// 优惠数目
int cutCount;

Product buy[KIND_NUM];

CutOff kindProcess[CUT_NUM][KIND_NUM];

int s[KIND_NUM][KIND_NUM][KIND_NUM][KIND_NUM][KIND_NUM];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

bool cmp(CutOff &left, CutOff &right)
{
	if (left.index < right.index)
	{
		return true;
	}
	return false;
}

bool cmp2(Product &left, Product &right)
{
	if (left.index < right.index)
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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/3.3.2 Shopping Offers/input9.txt";
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
	cin >> cutCount;
	for (int i = 1; i <= cutCount; ++i)
	{
		int kNum;
		cin >> kNum;
		cutNum[i] = kNum;
		for (int j = 1; j <= kNum; ++j)
		{
			CutOff cf;
			cin >> cf.index >> cf.count;
			kind[i][j] = cf;
		}
		cin >> cutPrice[i];
		sort(kind[i], kind[i] + kNum + 1, cmp);
	}
	int prodNum;
	cin >> prodNum;
	for (int i = 1; i <= prodNum; ++i)
	{
		int index, num, pri;
		cin >> index >> num >> pri;
		buy[i].index = index;
		buy[i].count = num;
		buy[i].price = pri;
	}
	sort(buy + 1, buy + prodNum + 1, cmp2);

	// 预处理cutoff
	for (int i = 1; i <= cutCount; ++i)
	{
		int index = 1;
		for (int j = 1; j < KIND_NUM; ++j)
		{
			if (buy[j].index == kind[i][index].index)
			{
				CutOff cf;
				cf.index = kind[i][index].index;
				cf.count = kind[i][index].count;
				kindProcess[i][j] = cf;
				++index;
			}
		}
	}

	for (int i1 = 0; i1 <= buy[1].count; ++i1)
	{
		for (int i2 = 0; i2 <= buy[2].count; ++i2)
		{
			for (int i3 = 0; i3 <= buy[3].count; ++i3)
			{
				for (int i4 = 0; i4 <= buy[4].count; ++i4)
				{
					for (int i5 = 0; i5 <= buy[5].count; ++i5)
					{
						// 遍历每一种优惠
						s[i1][i2][i3][i4][i5] = i1 * buy[1].price + i2 * buy[2].price + 
							i3 * buy[3].price + i4 * buy[4].price + i5 * buy[5].price;
						for (int j = 1; j <= cutCount; ++j)
						{
							int c1 = max(0, i1 - kindProcess[j][1].count);
							int c2 = max(0, i2 - kindProcess[j][2].count);
							int c3 = max(0, i3 - kindProcess[j][3].count);
							int c4 = max(0, i4 - kindProcess[j][4].count);
							int c5 = max(0, i5 - kindProcess[j][5].count);
							int tmp = s[c1][c2][c3][c4][c5] + cutPrice[j];
							if (s[i1][i2][i3][i4][i5] > tmp)
							{
								s[i1][i2][i3][i4][i5] = tmp;
							}
						}
					}
				}
			}
		}
	}
	cout << s[buy[1].count][buy[2].count][buy[3].count][buy[4].count][buy[5].count] << endl;
}

