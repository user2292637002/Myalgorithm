/*
题目描述：
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内藏有一定的现金，但不能偷连续的两间房（会触发警报）。
给定数组 nums，返回你能偷到的最高金额。

示例：
输入：nums = [1,2,3,1]
输出：4
解释：偷第 1 和第 3 间房，金额 = 1 + 3 = 4。

提示：
dp[i] 表示偷到第 i 间房时的最大金额。
状态转移：dp[i] = max(dp[i-1], dp[i-2] + nums[i])
即：不偷当前房（dp[i-1]） vs 偷当前房（dp[i-2] + nums[i]）

*/

#include<iostream>
#include<vector>>
#include<algorithm>
using namespace std;

int MaxEarning(vector<int> money)
{
	if (money.empty()) return 0;
	if (money.size() == 1) return 0;

	int n = money.size();

	int prev2 = 0;
	int prev1 = money[0];
	int maxEarn = 0;
	for (int i = 1; i < n; i++)
	{
		maxEarn = max(prev1, prev2 + money[i]);
		prev2 = prev1;
		prev1 = maxEarn;
	}
	return maxEarn;
}


int main()
{
	vector<int> money = {1,2,3,1};
	cout << MaxEarning(money) << endl;

	return 0;
}