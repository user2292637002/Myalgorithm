/*
题目描述：
给定一个字符串 s，请你找出其中不含有重复字符的 最长子串 的长度

示例：
输入: s = "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

提示：

*/

#include <iostream>
#include <unordered_set>
using namespace std;

int longestUniqueSubstring(const string& s)
{
    unordered_set<char> set;
    int left = 0, maxLen = 0;
    for (int right = 0; right < s.size(); ++right)
    {
        while (set.count(s[right]))      // 重复就缩左边界
            set.erase(s[left++]);
        set.insert(s[right]);
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

int main()
{
    string str;
    cin >> str;
    cout << longestUniqueSubstring(str); // 输入 abcabcbb -> 3
    return 0;
}