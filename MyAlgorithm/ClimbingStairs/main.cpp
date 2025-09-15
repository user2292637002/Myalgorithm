/*
题目描述：
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
注意：给定 n 是一个正整数。

示例：
输入: 2
输出: 2
解释: 有两种方法可以爬到楼顶。
1.  1 阶 + 1 阶
2.  2 阶

输入: 3
输出: 3
解释: 有三种方法可以爬到楼顶。
1.  1 阶 + 1 阶 + 1 阶
2.  1 阶 + 2 阶
3.  2 阶 + 1 阶

提示：
这是一个经典的动态规划问题。

设 dp[i] 表示爬到第 i 阶的方法数。
要到达第 i 阶，可以从第 i-1 阶爬 1 步，或从第 i-2 阶爬 2 步。
因此状态转移方程为：dp[i] = dp[i-1] + dp[i-2]。
初始条件：dp[1] = 1, dp[2] = 2。
由于 dp[i] 只依赖于前两个状态，我们可以用两个变量 prev1 和 prev2 来优化空间复杂度到 O(1)。

*/

#include<iostream>
using namespace std;

int ClimbStairs(int n)
{
	if (n <= 2) return n;

	int prev2 = 1;
	int prev1 = 2;
	int current = 0;

	for (int i = 3; i <= n; i++)
	{
		current = prev1 + prev2;
		prev2 = prev1;
		prev1 = current;
	}
	return current;
}

int main()
{
	int n;
	cin >> n;
	cout << ClimbStairs(n) << endl;
	return 0;
}