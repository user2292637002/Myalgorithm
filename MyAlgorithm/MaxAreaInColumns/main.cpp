#include<iostream>
#include<vector>
#include<stack>
using namespace std;

/// @brief 暴力解法：计算柱状图中最大矩形面积
/// @param heights 柱状图的高度数组
/// @return 返回最大矩形面积
/// 
/// 算法思路：
/// 枚举所有可能的矩形区间 [i, j]，计算以该区间为底、以区间内最小高度为高的矩形面积
/// 时间复杂度：O(n^2)，空间复杂度：O(1)
int Solution(const vector<int>& heights)
{
	int maxArea = 0;
	
	// 枚举所有可能的起始位置 i
	for (int i = 0; i < heights.size(); i++)
	{
		int minHeight = heights[i];  // 记录从 i 到当前 j 的最小高度
		
		// 枚举所有可能的结束位置 j（从 i 开始）
		for(int j = i; j < heights.size(); j++)
		{
			// 更新最小高度
			if (heights[j] < minHeight)
			{
				minHeight = heights[j];
			}
			
			// 计算以 [i, j] 为底、minHeight 为高的矩形面积
			int area = minHeight * (j - i + 1);
			
			// 更新最大面积
			if(area > maxArea)
				maxArea = area;
		}
	}
	return maxArea;
}

/// @brief 优化解法：使用单调栈计算柱状图中最大矩形面积
/// @param heights 柱状图的高度数组
/// @return 返回最大矩形面积
/// 
/// 算法思路（单调栈，时间复杂度 O(n)，空间复杂度 O(n)）：
/// 维护一个单调递增栈，栈中存储的是柱子的索引
/// 对于每个柱子，计算以它为高的最大矩形面积：
/// - 当遇到高度小于栈顶的柱子时，说明栈顶柱子的右边界确定了
/// - 弹出栈顶，计算以该柱子为高的矩形面积（宽度 = 右边界 - 左边界 - 1）
/// - 左边界是新的栈顶（如果栈为空则为 -1），右边界是当前索引 i
/// 
/// 为了处理所有柱子，在数组末尾添加一个高度为 0 的虚拟柱子
int Solution2(const vector<int>& heights)
{
	int maxArea = 0;
	stack<int> s;  // 单调递增栈，存储柱子的索引
	
	// 遍历所有柱子，包括一个虚拟的末尾柱子（高度为0）
	for (int i = 0; i <= heights.size(); i++)
	{
		// 如果 i 等于数组长度，使用高度 0（虚拟柱子），确保栈中所有元素都被处理
		int h = (i == heights.size() ? 0 : heights[i]);

		// 当当前高度小于栈顶柱子的高度时，说明栈顶柱子的右边界确定了
		while(!s.empty() && h < heights[s.top()])
		{
			// 弹出栈顶，计算以该柱子为高的矩形面积
			int height = heights[s.top()];
			s.pop();
			
			// 计算矩形宽度
			int right = i;  // 右边界是当前索引
			int left = s.empty() ? -1 : s.top();  // 左边界是新的栈顶（如果栈为空则为 -1）
			int width = right - left - 1;  // 宽度 = 右边界 - 左边界 - 1
			
			// 计算面积并更新最大值
			if(height * width > maxArea)
				maxArea = height * width;
		}
		
		// 将当前索引入栈
		s.push(i);
	}
	return maxArea;
}

int main()
{
	// 测试用例：柱状图高度数组
	// 柱状图：4, 3, 4, 3, 3, 4
	vector<int> height = { 4,3,4,3,3,4 };
	
	// 输出两种解法的结果（应该相同）
	cout << "暴力解法结果: " << Solution(height) << endl;
	cout << "单调栈解法结果: " << Solution2(height) << endl;
	return 0;
}