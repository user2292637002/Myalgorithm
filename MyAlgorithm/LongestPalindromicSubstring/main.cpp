/*
题目描述：给你一个字符串 s，找到 s 中最长的回文子串。
如果存在多个长度相同的最长回文子串，返回第一个。

示例：
输入: s = "babad"
输出: "bab"
解释: "aba" 也是一个有效答案。

输入: s = "cbbd"
输出: "bb"


提示：
使用中心扩展法 (Expand Around Centers)。

回文串的中心可能是一个字符（奇数长度），也可能是两个字符之间（偶数长度）。
遍历字符串中的每一个可能的中心点（共 2n-1 个：n 个单字符中心，n-1 个双字符中心）。
对于每个中心，向两边扩展，直到字符不再相等或到达边界。
记录扩展过程中遇到的最长回文串的起始位置和长度。

*/



#include<iostream>
#include<string>
using namespace std;


string LongestPalindrome(string s);

void ExpandAroundCenter(const string& s, int left, int right, int& start, int& maxLength);

int main()
{
	string str;
	cin >> str;
	cout << LongestPalindrome(str) << endl;
	return 0;
}


string LongestPalindrome(string s)
{
	if (s.empty()) return "";

	int start = 0; //用于记录起始位置
	int maxLength = 1; //用于记录长度

	// 遍历所有可能的中心位置
	for (int i = 0; i < s.length(); i++)
	{
		// 尝试以 s[i] 为中心的奇数长度回文
		ExpandAroundCenter(s, i, i, start, maxLength);

		// 尝试以 s[i] 和 s[i+1] 之间的间隙为中心的偶数长度回文
		ExpandAroundCenter(s, i, i + 1, start, maxLength);
	}

	return s.substr(start, maxLength);
}

// 从中心 (left, right) 向两边扩展
void ExpandAroundCenter(const string& s, int left, int right, int& start, int& maxLength)
{
	// 在边界内且字符相等时扩展
	while (left >= 0 && right < s.length() && s[left] == s[right])
	{
		int currentLength = right - left + 1;
		if (currentLength > maxLength)
		{
			maxLength = currentLength;
			start = left;
		}
		--left;
		++right;
	}
}