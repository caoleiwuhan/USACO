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

void BFS(unsigned a, unsigned b, unsigned c);

unsigned MaxOfThree(unsigned a, unsigned b, unsigned c);

unsigned NumberChange(unsigned a, unsigned b, unsigned c, unsigned base);

void PaserNumber(unsigned &a, unsigned &b, unsigned &c, unsigned num, unsigned base);

/*
	从a1到b1，
*/
void FromAToB(unsigned from, unsigned to, unsigned columnTo, 
	unsigned a1, unsigned b1, unsigned c1,	unsigned a2, unsigned b2, unsigned c2, 
	unsigned base, queue<unsigned> &q, set<unsigned> &s, set<unsigned> &res);

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/1.4.4 Mother's Milk/input5.txt";
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
	unsigned a, b, c;
	cin >> a >> b >> c;

	BFS(a, b, c);
}


void BFS(unsigned a, unsigned b, unsigned c)
{
	// 以最大值作为base，得出一个unsignend值
	unsigned base = MaxOfThree(a, b, c) + 1;

	unsigned tmp = NumberChange(0, 0, c, base);
	queue<unsigned> q;
	q.push(tmp);

	set<unsigned> ans;	
	ans.insert(tmp);

	set<unsigned> res;
	res.insert(c);

	
	while (!q.empty())
	{
		unsigned num = q.front();
		q.pop();
		unsigned a1, b1, c1;
		PaserNumber(a1, b1, c1, num, base);

		// a->b
		FromAToB(a1, b1, b, 0, a1+b1, c1, a1+b1-b, b, c1, base, q, ans, res);
		// a->c
		FromAToB(a1, c1, c, 0, b1, a1+c1, a1+c1-c, b1, c, base, q, ans, res);
		// b->a
		FromAToB(b1, a1, a, b1+a1, 0, c1, a, b1+a1-a, c1, base, q, ans, res);
		// b->c
		FromAToB(b1, c1, c, a1, 0, b1+c1, a1, b1+c1-c, c, base, q, ans, res);
		// c->a
		FromAToB(c1, a1, a, c1+a1, b1, 0, a, b1, c1+a1-a, base, q, ans, res);
		// c->b
		FromAToB(c1, b1, b, a1, c1+b1, 0, a1, b, c1+b1-b, base, q, ans, res);
	}

	int count = 0;
	for (set<unsigned>::iterator itr = res.begin(); itr != res.end(); ++itr, ++count)
	{
		if (count)
		{
			cout << ' ';
		}
		cout << *itr;
	}
	cout << endl;
}

unsigned MaxOfThree(unsigned a, unsigned b, unsigned c)
{
	return (a >= b ? 
			(a >= c ? a : c) :	// a >= b
			(b >= c ? b : c));
}

unsigned NumberChange(unsigned a, unsigned b, unsigned c, unsigned base)
{	
	return (a * base * base + b * base + c);
}

void PaserNumber(unsigned &a, unsigned &b, unsigned &c, unsigned num, unsigned base)
{
	c = num % base;
	num /= base;
	b = num % base;
	num /= base;
	a = num;
}

void FromAToB(unsigned from, unsigned to, unsigned columnTo, 
	unsigned a1, unsigned b1, unsigned c1,	unsigned a2, unsigned b2, unsigned c2, 
	unsigned base, queue<unsigned> &q, set<unsigned> &s, set<unsigned> &res)
{
	// 如果b已满
	if (to == columnTo)
	{
		return;
	}
	// 如果a为空
	if (from == 0)
	{
		return;
	}

	if (from + to <= columnTo)
	{ // 把a倒空
		unsigned curNum = NumberChange(a1, b1, c1, base);
		// 如果没找到
		if (s.find(curNum) == s.end())
		{
			q.push(curNum);
			s.insert(curNum);
			if (a1 == 0)
			{
				if (res.find(c1) == res.end())
				{
					res.insert(c1);
				}
			}
		}
	}
	else // 把b倒满
	{
		unsigned curNum = NumberChange(a2, b2, c2, base);
		if (s.find(curNum) == s.end())
		{
			q.push(curNum);
			s.insert(curNum);
			if (a2 == 0)
			{
				if (res.find(c2) == res.end())
				{
					res.insert(c2);
				}
			}
		}
	}
}