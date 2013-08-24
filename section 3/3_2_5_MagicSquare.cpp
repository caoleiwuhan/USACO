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

const int NUM = 8;



struct Node
{
	int arr[NUM];
	char ch;
	Node *parent;
};

Node* qu[10000];
int head, tail;

struct FindSame
{
	FindSame(Node *n)
	{
		node = n;
	}

	bool operator()(Node *right)
	{
		for (int i = 0; i < NUM; ++i)
		{
			if (right->arr[i] != node->arr[i])
			{
				return false;
			}
		}
		return true;
	}
	Node *node;
};

int target[8];

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

inline void Sample1(int *target, int *source)
{
	for (int i = 0; i < NUM; ++i)
	{
		target[i] = source[NUM - 1 - i];
	}
}

inline void Sample2(int *target, int *source)
{
	for (int i = 1; i < 4; ++i)
	{
		target[i] = source[i - 1];
		target[i+3] = source[i+4];
	}
	target[0] = source[3];
	target[7] = source[4];
}

inline void Sample3(int *target, int *source)
{
	target[0] = source[0];
	target[3] = source[3];
	target[4] = source[4];
	target[7] = source[7];

	target[1] = source[6];
	target[2] = source[1];
	target[5] = source[2];
	target[6] = source[5];
}

inline int ArrToHash(int *arr)
{
	int ans = 0;
	for (int i = 0; i < NUM; ++i)
	{
		ans = (arr[i] - 1) + ans * 8;
	}
	return ans;
}

void PrintAnswer(Node *ans, string &str);

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/3.2.5 Magic Squares/input5.txt";
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
	for (int i = 0; i < NUM; ++i)
	{
		cin >> target[i];
	}

	//queue<Node *> q;
	Node *n = new Node();
	set<Node *> s;
	

	for (int i = 0; i < NUM; ++i)
	{
		n->arr[i] = i + 1;
		n->parent = NULL;
	}
	//int arrHash = ArrToHash(n->arr);
	//aHash[arrHash] = true;
	//q.push(n);
	head = 0;
	tail = -1;
	qu[++tail] = n;
	s.insert(n);

	while (head <= tail)
	{
		Node *curNode = qu[head];
		head = (++head) % 10000;
		//q.pop();

		bool isAns = true;
		// 如果是结果
		for (int i = 0; i < NUM; ++i)
		{
			if (curNode->arr[i] != target[i])
			{
				isAns = false;
				break;
			}
		}
		if (isAns)
		{
			// 打印结果
			string ans;
			PrintAnswer(curNode, ans);
			cout << ans.length() << endl;
			cout << ans << endl;
			return;
		}
		Node *n1 = new Node();
		Sample1(n1->arr, curNode->arr);
		//int arrHash1 = ArrToHash(n1->arr);
		//if (!aHash[arrHash1])
		if (find_if(s.begin(), s.end(), FindSame(n1)) == s.end())
		{
			//aHash[arrHash1] = true;
			n1->ch = 'A';
			n1->parent = curNode;
			//q.push(n1);
			tail = (tail + 1) % 10000;
			qu[tail] = n1;

			s.insert(n1);
		}
		Node *n2 = new Node();
		Sample2(n2->arr, curNode->arr);
		//int arrHash2 = ArrToHash(n2->arr);
		//if (!aHash[arrHash2])
		if (find_if(s.begin(), s.end(), FindSame(n2)) == s.end())
		{
			//aHash[arrHash2] = true;
			n2->ch = 'B';
			n2->parent = curNode;
			//q.push(n2);
			tail = (tail + 1) % 10000;
			qu[tail] = n2;
			s.insert(n2);
		}		

		Node *n3 = new Node();
		Sample3(n3->arr, curNode->arr);
		//int arrHash3 = ArrToHash(n3->arr);
		//if (!aHash[arrHash3])
		if (find_if(s.begin(), s.end(), FindSame(n3)) == s.end())
		{
			//aHash[arrHash3] = true;
			n3->ch = 'C';
			n3->parent = curNode;
			//q.push(n3);
			tail = (tail + 1) % 10000;
			qu[tail] = n3;
			s.insert(n3);
		}
	}
}


void PrintAnswer(Node *ans, string &str)
{
	if (ans->parent == NULL)
	{
		return;
	}
	str.insert(0, 1, ans->ch);
	PrintAnswer(ans->parent, str);
}