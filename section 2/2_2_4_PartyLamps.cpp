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

#define CHANGE(addr, n) \
	((addr[n/32]) ^= (1 << (n % 32)))


const int MAXV = 101;

// 开着的
int on[MAXV];
// 关着的
int off[MAXV];

// 奇数 : 1,3
bool oddMap[8][4] =
{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1,
	0,1,1,1,
	1,0,1,1,
	1,1,0,1,
	1,1,1,0
};

// 偶数 : 0,2,4
bool evenMap[8][4] = 
{
	0,0,0,0,
	1,1,0,0,
	1,0,1,0,
	1,0,0,1,
	0,1,1,0,
	0,1,0,1,
	0,0,1,1,
	1,1,1,1
};

int N;

bool IsExist(vector<unsigned *> &ans, unsigned cur[]);

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

bool Cmp(unsigned *left, unsigned *right);

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/2.2.4 Party Lamps/input8.txt";
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

/*
	如果count是奇数：
		(4,1) (4,3)
			  偶数：
		(4,0) (4,2) (4,4)
*/	
void Process()
{
	cin >> N;
	int count;
	cin >> count;
	int onNum = 0;
	int offNum = 0;
	int tmp;
	while ((cin >> tmp) && (tmp != -1))
	{
		on[onNum++] = tmp;
	}
	while ((cin >> tmp) && (tmp != -1))
	{
		off[offNum++] = tmp;
	}
	unsigned init[4] = 
	{
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF
	};
	for (int i = N; i < 128; ++i)
	{
		CHANGE(init, i);
		//init[i/32] ^= 1 << (i % 32);
	}
		

	vector<unsigned *> ans;

	if (count == 0)
	{
		ans.push_back(init);
	}
	else
	{
		// 是奇数
		if (count & 1)
		{
			for (int i = 0; i < 8; ++i)
			{
				unsigned *cur = new unsigned[4];
				memcpy(cur, init, sizeof(unsigned) * 4);
				if (oddMap[i][0])
				{
					for (int i = 0; i < N; ++i)
					{
						CHANGE(cur, i);
					}
				}
				if (oddMap[i][1])
				{
					for (int i = 0; i < N; i += 2)
					{
						CHANGE(cur, i);
					}
				}
				if (oddMap[i][2])
				{
					for (int i = 1; i < N; i += 2)
					{
						CHANGE(cur, i);
					}
				}
				if (oddMap[i][3])
				{
					for (int i = 0; i < N; i += 3)
					{
						CHANGE(cur, i);
					}
				}
				if (!IsExist(ans, cur))
				{
					//ans.insert(cur);
					ans.push_back(cur);
				}
			}
		}
		else
		{
			for (int i = 0; i < 8; ++i)
			{
				unsigned *cur = new unsigned[4];
				memcpy(cur, init, sizeof(unsigned) * 4);
				if (evenMap[i][0])
				{
					for (int i = 0; i < N; ++i)
					{
						CHANGE(cur, i);
					}
				}
				if (evenMap[i][1])
				{
					for (int i = 0; i < N; i += 2)
					{
						CHANGE(cur, i);
					}
				}
				if (evenMap[i][2])
				{
					for (int i = 1; i < N; i += 2)
					{
						CHANGE(cur, i);
					}
				}
				if (evenMap[i][3])
				{
					for (int i = 0; i < N; i += 3)
					{
						CHANGE(cur, i);
					}
				}
				if (!IsExist(ans, cur))
				{
					//ans.insert(cur);
					ans.push_back(cur);
				}
			}
		}
	}
	
	//int size = ans.size();
	for (int i = 0; i < ans.size(); ++i)
	{
		bool isDel = false;
		unsigned *curTmp = ans[i];

		for (int j = 0; j < onNum; ++j)
		{
			int index = on[j] - 1;
			if (!(curTmp[index / 32] & (1 << (index % 32))))
			{
				isDel = true;
				ans.erase(ans.begin() + i);
				--i;
				break;
			}
		}
		if (!isDel)
		{
			for (int j = 0; j < offNum; ++j)
			{
				int index = off[j] - 1;
				if (curTmp[index / 32] & (1 << (index % 32)))
				{
					isDel = true;
					ans.erase(ans.begin() + i);
					--i;
					break;
				}
			}
		}
	}
	if (ans.size() == 0)
	{
		cout << "IMPOSSIBLE" << endl;
	}
	else
	{
		sort(ans.begin(), ans.end(), Cmp);

		for (vector<unsigned *>::iterator itr = ans.begin(); itr != ans.end(); ++itr)
		{
			unsigned *curTmp = (*itr);
			for (int i = 0; i < N; ++i)
			{
				//init[i/32] ^= 1 << (i % 32)
				cout << ((curTmp[i/32] & (1 << (i % 32))) >> (i % 32));
			}
			cout << endl;
		}
	}
	
}

bool IsExist(vector<unsigned *> &ans, unsigned cur[])
{
	for (vector<unsigned *>::iterator itr = ans.begin(); itr != ans.end(); ++itr)
	{
		bool isOK = true;
		for (int i = 0; i < 4; ++i)
		{
			if ((*itr)[i] != cur[i])
			{
				isOK = false;
				break;
			}
		}
		if (isOK)
		{
			return true;
		}
	}
	return false;
}


bool Cmp(unsigned *left, unsigned *right)
{
	for (int i = 0; i < N; ++i)
	{
		char a = ((left[i/32] & (1 << (i % 32))) >> (i % 32));
		char b = ((right[i/32] & (1 << (i % 32))) >> (i % 32));
		if (a != b)
		{
			return (a < b);
		}
	}
	return true;
	/*int index = 0;
	for (int i = 0; i < 4; ++i)
	{
		if (left[i] != right[i])
		{
			index = i;
			break;
		}
	}
	return (left[index] < right[index]);*/
}