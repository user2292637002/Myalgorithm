#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/// @brief 计算两个字符串的最长公共子序列（LCS）长度
/// @param text1 第一个字符串（以字符数组形式）
/// @param text2 第二个字符串（以字符数组形式）
/// @return 返回最长公共子序列的长度
/// 
/// 算法思路（动态规划，时间复杂度 O(m*n)，空间复杂度 O(m*n)）：
/// dp[i][j] 表示 text1[0..i-1] 和 text2[0..j-1] 的最长公共子序列长度
/// 
/// 状态转移方程：
/// - 如果 text1[i-1] == text2[j-1]，则 dp[i][j] = dp[i-1][j-1] + 1
/// - 否则，dp[i][j] = max(dp[i-1][j], dp[i][j-1])
/// 
/// 边界条件：dp[0][j] = 0, dp[i][0] = 0（空字符串与任何字符串的LCS长度为0）
int LCS(vector<char> text1, vector<char> text2)
{
	int m = text1.size();
	int n = text2.size();
	
	// 边界情况：如果任一字符串为空，LCS长度为0
	if(m == 0 || n == 0)
		return 0;
	
	// 创建二维DP数组，dp[i][j] 表示 text1[0..i-1] 和 text2[0..j-1] 的LCS长度
	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
	
	// 填充DP数组
	for(int i = 1; i <= m; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			// 如果当前字符匹配，LCS长度加1
			if(text1[i-1] == text2[j-1])
			{
				dp[i][j] = dp[i-1][j-1] + 1;
			}
			// 否则，取不包含当前字符的两种情况的最大值
			else
			{
				dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
			}
		}
	}
	
	return dp[m][n];
}

/// @brief 空间优化版本：计算两个字符串的最长公共子序列长度
/// @param text1 第一个字符串（以字符数组形式）
/// @param text2 第二个字符串（以字符数组形式）
/// @return 返回最长公共子序列的长度
/// 
/// 空间复杂度优化到 O(min(m,n))
/// 只保留当前行和上一行的DP值，使用滚动数组技术
int LCS_Optimized(vector<char> text1, vector<char> text2)
{
	int m = text1.size();
	int n = text2.size();
	
	// 边界情况
	if(m == 0 || n == 0)
		return 0;
	
	// 为了节省空间，使用较短的字符串长度作为DP数组大小
	if(m < n)
	{
		swap(text1, text2);
		swap(m, n);
	}
	
	// 只使用一维数组，prev 存储上一行的DP值，curr 存储当前行的DP值
	vector<int> prev(n + 1, 0);
	vector<int> curr(n + 1, 0);
	
	for(int i = 1; i <= m; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			// 如果当前字符匹配，LCS长度加1
			if(text1[i-1] == text2[j-1])
			{
				curr[j] = prev[j-1] + 1;
			}
			// 否则，取不包含当前字符的两种情况的最大值
			else
			{
				curr[j] = max(prev[j], curr[j-1]);
			}
		}
		// 更新prev为当前行，准备下一轮迭代
		prev = curr;
	}
	
	return curr[n];
}

int main()
{
	// 测试用例1：text1 = "abcde", text2 = "ace"
	// LCS = "ace"，长度为 3
	vector<char> text1 = {'a', 'b', 'c', 'd', 'e'};
	vector<char> text2 = {'a', 'c', 'e'};
	cout << "测试用例1:" << endl;
	cout << "text1: abcde, text2: ace" << endl;
	cout << "LCS长度: " << LCS(text1, text2) << endl;
	cout << "LCS长度(优化版): " << LCS_Optimized(text1, text2) << endl;
	cout << endl;
	
	// 测试用例2：text1 = "abc", text2 = "def"
	// LCS = ""，长度为 0
	vector<char> text3 = {'a', 'b', 'c'};
	vector<char> text4 = {'d', 'e', 'f'};
	cout << "测试用例2:" << endl;
	cout << "text1: abc, text2: def" << endl;
	cout << "LCS长度: " << LCS(text3, text4) << endl;
	cout << "LCS长度(优化版): " << LCS_Optimized(text3, text4) << endl;
	cout << endl;
	
	// 测试用例3：text1 = "abc", text2 = "abc"
	// LCS = "abc"，长度为 3
	vector<char> text5 = {'a', 'b', 'c'};
	vector<char> text6 = {'a', 'b', 'c'};
	cout << "测试用例3:" << endl;
	cout << "text1: abc, text2: abc" << endl;
	cout << "LCS长度: " << LCS(text5, text6) << endl;
	cout << "LCS长度(优化版): " << LCS_Optimized(text5, text6) << endl;
	
	return 0;
}
