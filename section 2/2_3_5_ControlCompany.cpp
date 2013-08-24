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

const int MAXV = 101;

set<int> company;

struct Node
{
	int to;
	int percent;
	Node *next;

	Node():next(0)
	{}
	Node (int _to, int _percent, Node *_next) : to(_to), percent(_percent), next(_next)
	{}

};

Node* hashNode[MAXV] = {0};

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/2.2.5 Controlling Companies/input3.txt";
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
	// 最大公司编号
	int N = 0;;
	int count;
	cin >> count;
	int start;
	int to;
	int percent;
	for (int i = 0; i < count; ++i)
	{
		cin >> start >> to >> percent;
		company.insert(start);
		company.insert(to);

		if (start > N)
		{
			N = start;
		}
		if (to > N)
		{
			N = to;
		}

		Node *next = hashNode[start];
		Node *n = new Node(to, percent, next);
		hashNode[start] = n;
	}

	for (set<int>::iterator itr = company.begin(); itr != company.end(); ++itr)
	{
		int i = (*itr);
		for (set<int>::iterator itr2 = company.begin(); itr2 != company.end(); ++itr2)
		{
			int j = (*itr2);
			if (j == i)
			{
				continue;
			}
			// 1.直接控股
			Node *head = hashNode[i];
			bool isOK = false;
			while (head)
			{
				if ((head->to == j) && head->percent > 50)
				{
					cout << i << ' ' << j << endl;
					isOK = true;
					break;
				}
				head = head->next;
			}
			// 间接控股
			if (!isOK)
			{
				double asc = 0;
				head = hashNode[i];
				while (head)
				{
					double num1 = head->percent / 100.0;
					int to = head->to;
					Node *toHead = hashNode[to];
					while (toHead)
					{
						if (toHead->to == j)
						{
							double num2 = toHead->percent / 100.0;
							asc += num1 * num2;
							break;
						}
						toHead = toHead->next;
					}
					head = head->next;
				}
				if (asc > 0.5)
				{
					cout << i << ' ' << j << endl;
				}
			}
		}
	}

}

