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

const int MAXV = 4096;

int freq[13][MAXV];

struct Node
{
	int num;
	int len;
	int frequent;

	Node(int _num, int _len, int _fre) : num(_num), len(_len), frequent(_fre) {}
};

inline bool Cmp(Node *left, Node *right)
{
	if (left->frequent > right->frequent)
	{
		return true;
	}
	else if (left->frequent < right->frequent)
	{
		return false;
	}
	else
	{
		if (left->len < right->len)
		{
			return true;
		}	
		else if (left->len > right->len)
		{
			return false;
		}
		else 
		{
			if (left->num < right->num)
			{
				return true;
			}
			return false;
		}		
	}
}

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

inline int ParseStringToInt(string &str)
{
	int ans = 0;
	int len = str.length();
	for (int i = 0; i < len; ++i)
	{
		ans <<= 1;
		if (str[i] == '1')
		{
			ans += 1;
		}
	}
	return ans;
}

inline string ParseIntToStr(int num, int len)
{
	string str;
	int index = 0;
	while (num)
	{
		if (num & 1)
		{
			str.insert(0, 1, '1');
		}
		else
		{
			str.insert(0, 1, '0');
		}
		num >>= 1;
		++index;
	}
	while (index < len)
	{
		str.insert(0, 1, '0');
		++index;
	}
	return str;
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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/3.1.5 Contact/input5.txt";
	//string inputStr = "D:/2挑战编程/input/110205.inp";
	string outputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/3.1.5 Contact/out.txt";
	ifstream fin;
	fin.open(inputStr);	

	cin.rdbuf(fin.rdbuf());	

	ofstream fout;
	fout.open(outputStr);

	cout.rdbuf(fout.rdbuf());
#endif

	Process();

}


void Process()
{	
	int low, up, count;
	cin >> low >> up >> count;

	string str;
	string seq;
	cin.ignore();
	while (getline(cin, str))
	{
		seq += str;
	}
	// 统计
	int len = seq.length();
	for (int i = 0; i < len; ++i)
	{
		for (int j = low; j <= up; ++j)
		{
			if (i + j <= len)
			{
				string sub = seq.substr(i, j);

				int num = ParseStringToInt(sub);

				++freq[j][num];
			}
		}
	}
	vector<Node *> vec;
	for (int i = low; i <= up; ++i)
	{
		for (int j = 0; j < MAXV; ++j)
		{
			int f = freq[i][j];
			if (f)
			{
				Node *n = new Node(j, i, f);
				vec.push_back(n);
			}
		}
	}
	// 对其进行排序
	sort(vec.begin(), vec.end(), Cmp);
	int lastFreq = -1;
	int size = vec.size();
	for (int i = 0, j = 0; (i < count) && (j < size); ++i)
	{
		Node *n = vec[j++];
		if (n->frequent != lastFreq)
		{
			if (lastFreq != -1)
			{
				cout << endl;
			}
			cout << n->frequent << endl;
			cout << ParseIntToStr(n->num, n->len);
			
			lastFreq = n->frequent;

			int curCount = 1;

			if (j < size)
			{
				n = vec[j];
				while (n->frequent == lastFreq)
				{
					if (curCount == 6)
					{
						curCount = 0;
						cout << endl;
					}
					else
					{
						cout << ' ';
					}
					++curCount;

					cout << ParseIntToStr(n->num, n->len);
					lastFreq = n->frequent;

					++j;
					if (j < size)
					{
						n = vec[j];
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	cout << endl;
}


