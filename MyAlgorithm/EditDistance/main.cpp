#include<iostream>
#include<vector>
using namespace std;

class  Solution
{
public:
	int minDistance(string word1, string word2)
	{
		int m = word1.size();
		int n = word2.size();
		// dp[i][j]表示word1的前i个字符和word2的前j个字符之间的编辑距离
		vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

		// 初始化边界条件
		for (int i = 0; i <= m; ++i) dp[i][0] = i;
		for (int j = 0; j <= n; ++j) dp[0][j] = j;
 	}
};




int main()
{

}