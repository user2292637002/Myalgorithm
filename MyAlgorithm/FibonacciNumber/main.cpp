/*
题目描述：
计算斐波那契数列的第 n 项。F(0) = 0, F(1) = 1, F(n) = F(n-1) + F(n-2)

示例：
输入：n = 4
输出：3
解释：F(4) = F(3) + F(2) = 2 + 1 = 3
*/


#include<iostream>
using namespace std;


int Fibonacci(int n)
{
	if (n <= 1) return n;

	int f1 = 0;
	int f2 = 1;


	int fn = 0;
	for (int i = 2; i <= n; i++)
	{
		fn = f1 + f2;
		f1 = f2;
		f2 = fn;
	}
	return fn;
}


int main()
{
	int n;
	cin >> n;
	cout << Fibonacci(n) << endl;
	return 0;
}