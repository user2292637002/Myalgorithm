/*
题目描述：
给出一个区间的集合，合并所有重叠的区间。

示例：
输入: intervals = [[1,3],[2,6],[8,10],[15,18]]
输出: [[1,6],[8,10],[15,18]]
解释: 区间 [1,3] 和 [2,6] 重叠，合并为 [1,6]。

提示：
先按区间的起始位置排序。
遍历区间，如果当前区间的起点 ≤ 上一个区间的终点，则合并（更新终点为最大值）。
否则，将当前区间加入结果。

*/

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

vector<vector<int>> MergeIntervals(vector<vector<int>> intervals)
{
	if (intervals.empty()) return {};

	sort(intervals.begin(), intervals.end());
	
	vector<vector<int>> merged;
	merged.push_back(intervals[0]);
	for (int i = 0; i < intervals.size(); i++)
	{
		if (intervals[i][0] <= merged.back()[1])
		{
			merged.back()[1] = max(merged.back()[1], intervals[i][1]);
		}
		else
		{
			merged.push_back(intervals[i]);
		}
	}
	return merged;
}

int main()
{
	vector<vector<int>> intervals = { {1,3},{2,6},{8,10},{15,18} };

	auto merged = MergeIntervals(intervals);

	cout << "[";
	for (int i = 0; i < merged.size(); i++)
	{
		cout << "[";
		for (int j = 0; j < merged[i].size(); j++)
		{
			cout << merged[i][j];
			if (j != merged[i].size() - 1)
				cout << ",";
		}
		cout << "]";
		if (i != merged.size()-1)
		cout << ",";
	}
	cout << "]";
}