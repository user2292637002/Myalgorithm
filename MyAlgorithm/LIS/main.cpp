#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/// @brief 计算最长递增子序列（LIS）的长度
/// @param arr 输入数组
/// @return 返回最长递增子序列的长度
/// 
/// 算法思路（贪心 + 二分查找，时间复杂度 O(n log n)）：
/// 维护一个 tails 数组，其中 tails[i] 表示长度为 i+1 的所有递增子序列中，末尾元素的最小值
/// tails 数组是单调递增的，因此可以使用二分查找来优化
/// 
/// 对于每个元素 x：
/// 1. 如果 x 大于 tails 中所有元素，说明可以形成更长的子序列，将 x 添加到 tails 末尾
/// 2. 否则，找到第一个大于等于 x 的位置，用 x 替换它（贪心策略：保持末尾元素尽可能小）
int LIS(const vector<int>& arr)
{
	if (arr.empty())
		return 0;
	
	// tails[i] 表示长度为 i+1 的所有递增子序列中，末尾元素的最小值
	// 这个数组始终保持单调递增，可以用二分查找优化
	vector<int> tails;
	
	// 遍历数组中的每个元素
	for (int x : arr)
	{
		// 在 tails 中查找第一个大于等于 x 的位置（二分查找）
		auto it = lower_bound(tails.begin(), tails.end(), x);
		
		// 如果 x 大于 tails 中所有元素，说明可以形成更长的子序列
		if(it == tails.end())
			tails.push_back(x);  // 将 x 添加到 tails 末尾
		else
			*it = x;  // 用 x 替换找到的位置（贪心：保持末尾元素尽可能小，为后续元素留出空间）
	}
	
	// tails 数组的长度就是最长递增子序列的长度
	return tails.size();
}

int main()
{
	// 测试用例：数组 {10,9,2,5,3,7,101,18}
	// 最长递增子序列为 {2,3,7,18} 或 {2,5,7,18}，长度为 4
	vector<int> arr = { 10,9,2,5,3,7,101,18 };
	cout << "Length of LIS: " << LIS(arr) << endl;
	return 0;
}