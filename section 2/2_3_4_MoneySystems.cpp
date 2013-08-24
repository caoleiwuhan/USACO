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

////////////////////////////////////////////////////////////////////////


class HP
{
public:
	// 最大长度
	static const int MAXL = 1010;
	// 数制
	static const int BASE = 10;
	// 长度
	int len;
	// 保存每一位
	int s[MAXL];

	HP() 
	{ 
		memset(s, 0, sizeof(s));
		(*this) = 0; 
	};
	HP(int inte) 
	{ 
		memset(s, 0, sizeof(s));
		(*this) = inte; 
	};
	HP(const char* str) 
	{ 
		memset(s, 0, sizeof(s));
		(*this) = str; 
	};
	HP(string str) 
	{
		memset(s, 0, sizeof(s));
		(*this) = str; 
	};

	friend ostream& operator << (ostream &cout, const HP &x);

	HP operator = (int inte);
	HP operator = (const char* str); 
	HP operator = (string str);

	HP operator + (const HP &b); HP operator += (const HP &b);
	HP operator - (const HP &b); HP operator -= (const HP &b);
	HP operator * (const HP &b); HP operator *= (const HP &b);
	HP operator / (const HP &b); HP operator /= (const HP &b);
	HP operator % (const HP &b); HP operator %= (const HP &b);

	int comp(const HP &b);

	bool operator > (const HP &b); bool operator < (const HP &b);
	bool operator >= (const HP &b); bool operator <= (const HP &b);
	bool operator == (const HP &b); bool operator != (const HP &b);
};

ostream& operator << (ostream &cout, const HP &x)
{
	for (int i = x.len - 1; i >= 0; --i) 
	{
		cout << x.s[i];
	}
	return cout;
}

HP HP::operator = (int inte)
{
	if (inte == 0)
	{
		len = 1;
		s[0] = 0;
	}
	else
	{
		len = 0;
		while (inte)
		{
			s[len++] = inte % BASE;
			inte /= BASE;
		}
	}
	return (*this);
}

HP HP::operator = (const char* str)
{
	len = strlen(str);
	for (int i = 0; i != len; ++i) 
		s[i] = int(str[len - 1 - i] - '0');
	return (*this);
}

HP HP::operator = (string str)
{
	len = str.size();
	for (int i = 0; i != len; ++i) 
		s[i] = int(str[len - 1 - i] - '0');
	return (*this);
}

HP HP::operator + (const HP &b)
{
	HP c;
	c.s[0] = 0;
	for (int i = 0; i < len || i < b.len; ++i)
	{
		if (i < len) 
			c.s[i] += s[i];
		if (i < b.len) 
			c.s[i] += b.s[i];
		c.s[i + 1] = c.s[i] / BASE;
		c.s[i] %= BASE;
	}
	c.len = max(len, b.len) + 1;
	while (c.len > 1 && !c.s[c.len - 1]) 
		--c.len;
	return c;
}

HP HP::operator - (const HP &b)
{
	HP c = (*this);
	// 保证c > b
	int numLen = c.len;
	for (int i = 0; i != numLen; ++i)
	{
		c.s[i] -= b.s[i];
		if (c.s[i] < 0)
		{
			c.s[i] += BASE;
			--c.s[i + 1];
		}
	}
	while (c.len > 1 && !c.s[c.len - 1]) 
		--c.len;
	return c;
}

HP HP::operator * (const HP &b)
{
	HP c;
	for (int i = 0; i != len + b.len; ++i) 
		c.s[i] = 0;
	for (int i = 0; i != len; ++i)
		for (int j = 0; j != b.len; ++j)
		{
			c.s[i + j] += s[i] * b.s[j];
			c.s[i + j + 1] += c.s[i + j] / BASE;
			c.s[i + j] %= BASE;
		}
		c.len = len + b.len;
		while (c.len > 1 && !c.s[c.len - 1]) 
			--c.len;
		return c;
}

HP HP::operator / (const HP &b)
{
	HP c, d;
	if (b.len == 1 && b.s[0] == 0) 
		return c;
	for (int i = len - 1; i >= 0; --i)
	{
		if (d.len != 1 || d.s[0] != 0)
		{
			for (int j = d.len; j > 0; --j)
				d.s[j] = d.s[j - 1];
			++d.len;
		}
		d.s[0] = s[i];
		c.s[i] = 0;
		while (d >= b)
		{
			d -= b;
			++c.s[i];
		}
	}
	c.len = len;
	while (c.len > 1 && !c.s[c.len - 1]) 
		--c.len;
	return c;
}

HP HP::operator % (const HP &b)
{
	HP d;
	if (b.len == 1 && b.s[0] == 0) 
		return d;
	for (int i = len - 1; i >= 0; --i)
	{
		if (d.len != 1 || d.s[0] != 0)
		{
			for (int j = d.len; j > 0; --j)
				d.s[j] = d.s[j - 1];
			++d.len;
		}
		d.s[0] = s[i];
		while (d >= b) d -= b;
	}
	return d;
}

int HP::comp(const HP &b)
{
	if (len > b.len) return 1;
	if (len < b.len) return -1;
	int i = len - 1;
	while ((i > 0) && (s[i] == b.s[i])) 
		--i;
	return s[i] - b.s[i];
}

HP HP::operator += (const HP &b)
{
	(*this) = (*this) + b;
	return (*this);
}

HP HP::operator -= (const HP &b)
{
	(*this) = (*this) - b;
	return (*this);
}

HP HP::operator *= (const HP &b)
{
	(*this) = (*this) * b;
	return (*this);
}

HP HP::operator /= (const HP &b)
{
	(*this) = (*this) / b;
	return (*this);
}

HP HP::operator %= (const HP &b)
{
	(*this) = (*this) % b;
	return (*this);
}
bool HP::operator > (const HP &b) { return this->comp(b) > 0; }
bool HP::operator < (const HP &b) { return this->comp(b) < 0; }
bool HP::operator >= (const HP &b) { return this->comp(b) >= 0; }
bool HP::operator <= (const HP &b) { return this->comp(b) <= 0; }
bool HP::operator == (const HP &b) { return this->comp(b) == 0; }
bool HP::operator != (const HP &b) { return this->comp(b) != 0; }


////////////////////////////////////////////////////////////////////////

// 硬币数
const int MAXV = 26;
// 硬币种类
int coins[MAXV];

HP s[10001][MAXV];

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
	string inputStr = "C:/Users/cao/Desktop/算法/USACO/USACO全部测试数据/2.2.4 Money Systems/input10.txt";
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
	int V, N;
	cin >> V >> N;
	coins[0] = 0;
	for (int i = 1; i <= V; ++i)
	{
		cin >> coins[i];
	}
	sort(coins, coins + V + 1);
	for (int i = 1; i <= N; ++i)
	{
		if (i % coins[1] == 0)
		{
			s[i][1] = 1;
		}
	}
	

	// 钱数为i，最大面值为coins[j]的个数
	for (int i = coins[1] + 1; i <= N; ++i)
	{
		for (int j = 2; (j <= V) && (i >= coins[j]); ++j)
		{
			int num = coins[j];
			HP kind = 0;

			for (int k = 1; k * num < i; ++k)
			{
				for (int t = j - 1; t > 0; --t)
				{
					kind += s[i-k*num][t];
				}					
			}
			if (i % coins[j] == 0)
			{
				kind += 1;
			}
			s[i][j] = kind;
		}
	}
	HP ans = 0;
	for (int i = 1; i <= V; ++i)
	{
		ans += s[N][i];
		//cout << s[N][i] << endl;
	}
	cout << ans << endl;
}