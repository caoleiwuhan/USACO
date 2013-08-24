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

string maps[10] = 
{
	"",
	"0",
	"00",
	"000",
	"01",
	"1",
	"10",
	"100",
	"1000",
	"02",
};

int ans[10];

char NUM[10] = 
{
	'I',
	'V',
	'X',
	'L',
	'C',
	'D',
	'M'
};

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

void ParseNum(int num);

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/2.2.1 Preface Numbering/input8.txt";
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
	int N;
	cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		ParseNum(i);
	}
	for (int i = 0; i < 7; ++i)
	{
		if (ans[i])
		{
			cout << NUM[i] << ' ' << ans[i] << endl;
		}
	}

	//ParseNum(1);
	//ParseNum(3);
	//ParseNum(4);
	//ParseNum(5);
	//ParseNum(7);
	//ParseNum(8);
	//ParseNum(9);
	//ParseNum(10);

	//ParseNum(11);
	//ParseNum(14);
	//ParseNum(18);
	//ParseNum(19);
	//ParseNum(40);
	//ParseNum(45);
	//ParseNum(49);
	//ParseNum(66);
	//ParseNum(78);
	//ParseNum(89);
	//ParseNum(92);
	//ParseNum(99);

	//ParseNum(438);
	//ParseNum(494);
	//ParseNum(532);
	//ParseNum(587);
	//ParseNum(932);
	//ParseNum(1005);
	

}

void ParseNum(int num)
{
	//string tmp = "";
	int power = 0;	
	while (num)
	{
		int remain = num % 10;
		num /= 10;
		string str = maps[remain];
		//int pos = 0;
		for (int i = 0; i < str.length(); ++i)
		{
			int index = (str[i] - '0');
			++ans[index + power];
			//tmp.insert(pos++, 1, (str[i] + power));
		}
		power += 2;
	}
	//cout << tmp << endl;
}
