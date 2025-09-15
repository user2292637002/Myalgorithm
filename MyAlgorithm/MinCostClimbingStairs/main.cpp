/*
题目描述：
数组 cost 表示每级台阶的花费，你可以从第 0 级或第 1 级开始，每次可以爬 1 或 2 级。
到达楼梯顶部（即超过最后一级台阶）时停止。求最小花费。

示例：
输入：cost = [10, 15, 20]
输出：15
解释：从下标为 1 的台阶开始，花费 15，爬两步到顶部。总花费 15。

提示：
dp[i] 表示到达第 i 级台阶的最小花费。
状态转移：dp[i] = min(dp[i-1], dp[i-2]) + cost[i]
最终答案是 min(dp[n-1], dp[n-2])，因为可以从最后两级跳到顶部。

*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int MinCostClimbStairs(vector<int> cost)
{
	int n = cost.size();
	if (n <= 1)
		return 0;
	

	int prev2 = cost[0];
	int prev1 = cost[1];
	int minCost = 0;
	for (int i = 2; i <= n; i++)
	{
		int currentCost = (i == n) ? 0 : cost[i];
		minCost = min(prev2, prev1) + currentCost;
		prev2 = prev1;
		prev1 = minCost;
	}
	return minCost;
}


int main()
{
	vector<int> cost = { 10,15,20 };

	cout << MinCostClimbStairs(cost) << endl;
	return 0;
}