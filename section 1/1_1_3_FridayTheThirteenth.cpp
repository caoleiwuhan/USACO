#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define _MY_DEBUG_

// 一周7天
const int DAY_OF_WEEKDAY = 7;
// 一年12个月
const int MONTH_OF_YEAR = 12;

// 13号每一个的个数
int weekday[DAY_OF_WEEKDAY];

int months[MONTH_OF_YEAR] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};



/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

// 是否是闰年
bool IsRunYear(int year);

/*
	测试闰年
*/
void TestRunYear();

int main()
{
	MainStructure();
	return 0;
}

void MainStructure()
{
	
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/1.1.3 Friday the Thirteenth/input8.txt";
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
	//TestRunYear();
}

void Process()
{
	int year;
	cin >> year;
	// 从1990年1月0号开始,sunday:0,monday:1
	int totalDay = 0;

	// 年数
	for (int i = 0; i < year; ++i)
	{
		// 一年的12个月
		for (int j = 0; j < MONTH_OF_YEAR; ++j)
		{
			totalDay += 13;
			int remain = totalDay % DAY_OF_WEEKDAY;
			++weekday[remain];

			totalDay -= 13;

			// 如果是2月，且是闰年
			if (j == 1 && IsRunYear(1900 + i))
			{
				totalDay += 29;
			}
			else
			{
				totalDay += months[j];
			}
		}
	}
	// 输出
	// 周六
	cout << weekday[6];
	for (int i = 0; i < 6; ++i)
	{
		cout << ' ' << weekday[i];
	}
}


bool IsRunYear(int year)
{
	if (((year % 100 != 0) && (year % 4 == 0)) ||
		(year % 400 == 0))
	{
		return true;
	}
	return false;
}


void TestRunYear()
{
	cout << IsRunYear(1900) << endl;
	cout << IsRunYear(1901) << endl;
	cout << IsRunYear(1902) << endl;
	cout << IsRunYear(1903) << endl;
	cout << IsRunYear(1904) << endl;
	cout << IsRunYear(1905) << endl;
	cout << IsRunYear(2000) << endl;
}