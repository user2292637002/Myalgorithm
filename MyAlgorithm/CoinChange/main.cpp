/*
题目描述：
给定不同面额的硬币 coins 和一个总金额 amount。返回凑成总金额所需的最少硬币数。如果无法凑成，返回 -1。

示例：
输入：coins = [1, 2, 5], amount = 11
输出：3
解释：11 = 5 + 5 + 1，最少 3 枚。

提示：
dp[i] 表示凑出金额 i 所需的最少硬币数。
状态转移：dp[i] = min(dp[i - coin] + 1)，对所有 coin <= i
初始：dp[0] = 0，其余设为 INT_MAX

*/

#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int CoinChange(vector<int> coin,int amount)
{
	vector<int> dp(amount + 1, INT_MAX);
	dp[0] = 0;

	for (int i = 0; i <= amount; i++)
	{
		for (int ci : coin)
		{
			if (ci <= i && dp[i - ci] != INT_MAX)
			{
				dp[i] = min(dp[i], dp[i - ci] + 1);
			}
		}
	}
	return dp[amount];

}


int main()
{
	vector<int> coin= {1, 2, 5};
	int amount = 11;
	cout << CoinChange(coin, amount);
	return 0;
}