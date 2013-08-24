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

// 最大的farmer数
const int MAXV = 6001;
// 
struct Farmer
{
	// 单价
	int price;
	// 供应量
	int amount;
};

// 保存所有农场主
Farmer farmers[MAXV];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

/*
	排序函数
*/
bool Cmp(const Farmer &f1, const Farmer &f2);


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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/1.3.1 Mixing Milk/milk.in6";
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
	// 总量
	int total;
	// 农场主数目
	int farmNum;
	cin >> total >> farmNum;
	for (int i = 0; i < farmNum; ++i)
	{
		cin >> farmers[i].price >> farmers[i].amount;
	}
	// 按照价格从低到高排序,如果价格相等，按照量从大到小
	sort(farmers, farmers + farmNum, Cmp);
	// 总花费
	int cost = 0;
	for (int i = 0; i < farmNum; ++i)
	{
		if (total >= farmers[i].amount)
		{
			cost += farmers[i].amount * farmers[i].price;
			total -= farmers[i].amount;
		}
		else
		{
			cost += total * farmers[i].price;
			break;
		}
	}
	cout << cost << endl;

}

//bool Cmp(const Farmer &f1, const Farmer &f2)
//{
//	if (f1.price < f2.price)
//	{
//		return true;
//	}
//	else if (f1.price > f2.price)
//	{
//		return false;
//	}
//	else
//	{
//		if (f1.amount >= f2.amount)
//		{
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//}

bool Cmp(const Farmer &f1, const Farmer &f2)
{
	if (f1.price < f2.price)
	{
		return true;
	}
	else 
	{
		return false;
	}
}