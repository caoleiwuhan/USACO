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

// 种类数
const int KIND = 26;

// 所需营养
int needs[KIND];

// 每一种饲料包含的营养数
int everyHol[16][KIND];

// 剩余的营养
int remain[KIND];

struct Node
{
	int id;
	int *curHol;
	int len;
	Node *parent;
};

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

Node* BFS(int needNum, int kindNum);

void PrintAns(Node *ans);

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/2.1.4 Healthy Holsteins/input10.txt";
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
	// 所需数
	int needNum = 0;
	cin >> needNum;
	for (int i = 0; i < needNum; ++i)
	{
		cin >> needs[i];
	}
	// 饲料种类
	int kindNum = 0;
	cin >> kindNum;
	for (int i = 0; i < kindNum; ++i)
	{
		for (int j = 0; j < needNum; ++j)
		{
			cin >> everyHol[i][j];
			remain[j] += everyHol[i][j];
		}
	}
	Node *ans = BFS(needNum, kindNum);
	cout << ans->len;
	PrintAns(ans);
	cout << endl;
}

Node* BFS(int needNum, int kindNum)
{
	Node *n = new Node();
	n->id = -1;
	n->parent = NULL;
	n->curHol = new int[KIND];
	n->len = 0;
	for (int i = 0; i < needNum; ++i)
	{
		n->curHol[i] = 0;
	}

	queue<Node *> q;
	q.push(n);
	while (!q.empty())
	{
		Node *curNode = q.front();
		q.pop();
		bool isOK = true;
		for (int i = 0; i < needNum; ++i)
		{
			if (curNode->curHol[i] < needs[i])
			{
				isOK = false;
				break;
			}
		}
		if (isOK)
		{
			return curNode;
		}


		for (int i = (curNode->id + 1); i < kindNum; ++i)
		{
			//bool isOK = true;
			// 是否满足条件：如果后面所有的都加进去也不够，则不成立
			//for (int j = 0; j < needNum; ++j)
			//{// 有一种不够，则不成立
			//	if (needs[j] > remain[j])
			//	{
			//		isOK = false;
			//		break;
			//	}
			//}
			//if (isOK)
			{
				Node *nextNode = new Node();
				nextNode->id = i;
				nextNode->parent = curNode;
				nextNode->len = curNode->len + 1;
				nextNode->curHol = new int[KIND];
				for (int j = 0; j < needNum; ++j)
				{
					nextNode->curHol[j] = curNode->curHol[j] + everyHol[i][j];
				}
				q.push(nextNode);
			}
		}
	}
}

void PrintAns(Node *ans)
{
	if (ans->id != -1)
	{
		PrintAns(ans->parent);
		cout << ' ' << (ans->id + 1);
	}
}