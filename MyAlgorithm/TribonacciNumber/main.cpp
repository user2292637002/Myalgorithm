/*
题目描述：
泰波那契序列：T(0)=0, T(1)=1, T(2)=1, T(n) = T(n-1) + T(n-2) + T(n-3)
给定 n，返回 T(n)。

示例：
输入：n = 4
输出：4
解释：T(3)=2, T(4)=1+1+2=4


*/

#include<iostream>
using namespace std;

int Tribonacci(int n)
{
	if (n <= 1) return n;
	if (n == 2) return n - 1;
	int t0 = 0;
	int t1 = 1;
	int t2 = 1;
	int tn;
	for (int i = 3; i <= n; i++)
	{
		tn = t0 + t1 + t2;
		t0 = t1;
		t1 = t2;
		t2 = tn;
	}
	return tn;
}

int main()
{
	int n;
	cin >> n;
	cout << Tribonacci(n) << endl;
	return 0;
}