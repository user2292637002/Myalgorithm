#include<iostream>
#include<vector>
using namespace std;


/*
简述：康托展开是一个全排列到一个自然数的双射，常用于构建hash表时的空间压缩。设有n个数（1，2，3，4,…,n），可以有组成不同(n!种)的排列组合，康托展开表示的就是在n个不同元素的全排列中, 比当前排列组合小的个数，那么也可以表示当前排列组合在n个不同元素的全排列中的名次（当前的名次 = 比当前排列组合小的个数 + 1）。


原理：对于一个长度为n的排列P = p1 p2 p3 ... pn，康托展开的计算方法如下：
1. 对于排列P中的每一个元素pi（i从1到n），计算在pi后面且小于pi的元素个数，记为ci。
2. 康托展开的值C可以通过以下公式计算：
   C = c1 * (n-1)! + c2 * (n-2)! + ... + cn-1 * 1! + cn * 0!
3. 最终的康托展开值C表示排列P在所有排列中的排名（从0开始计数），如果需要从1开始计数，则需要加1。

例如：对于排列P = 3 1 4 2：
- 对于3，后面有2个元素（1和2）小于3，所以c1 = 2。
- 对于1，后面没有元素小于1，所以c2 = 0。
- 对于4，后面有1个元素（2）小于4，所以c3 = 1。
- 对于2，后面没有元素小于2，所以c4 = 0。
- 康托展开值C = 2 * 3! + 0 * 2! + 1 * 1! + 0 * 0! = 12 + 0 + 1 + 0 = 13。
*/


class Solution
{
public:
	int cantor(string str)
	{
		int n = str.size();
		int factorial[16];
		factorial[0] = 1;
		for (int i = 1; i <= 15; ++i)
		{
			factorial[i] = factorial[i - 1] * i;
		}
		int result = 0;
		for (int i = 0; i < n; ++i)
		{
			int count = 0;
			for (int j = i + 1; j < n; ++j)
			{
				if (str[j] < str[i])
				{
					++count;
				}
			}
			result += count * factorial[n - 1 - i];
		}
		return result + 1; // 名次从1开始
	}

	string deCantor(int rank, int n)
	{
		int factorial[16];
		factorial[0] = 1;
		for (int i = 1; i <= 15; ++i)
		{
			factorial[i] = factorial[i - 1] * i;
		}
		rank -= 1; // 转换为从0开始计数
		string str;
		for (int i = 1; i <= n; ++i)
		{
			str += (i + '0');
		}
		string result;
		vector<bool> used(n + 1, false);
		for (int i = 0; i < n; ++i)
		{
			int fact = factorial[n - 1 - i];
			int index = rank / fact;
			rank %= fact;
			int count = -1;
			for (int j = 1; j <= n; ++j)
			{
				if (!used[j])
				{
					++count;
				}
				if (count == index)
				{
					result += (j + '0');
					used[j] = true;
					break;
				}
			}
		}
		return result;
	}
};


int main()
{
	return 0;
}