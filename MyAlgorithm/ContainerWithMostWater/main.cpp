/*
题目描述：
给定一个长度为 n 的非负整数数组 height。每个元素 height[i] 表示第 i 条线的高度，
坐标 (i, 0) 到 (i, height[i])。找出两条线，使得它们与 x 轴构成的容器可以容纳最多的水。

示例：
输入：height = [1,8,6,2,5,4,8,3,7]
输出：49
解释：图中垂直线代表输入数组，蓝色部分表示可以盛水的区域，最大面积为 49。

提示：
使用左右两个指针，分别指向数组首尾。
水的面积 = min(height[left], height[right]) * (right - left)
每次移动较短的那条边的指针，因为面积由短板决定，移动长板不会增加面积。
*/



#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int MaxArea(vector<int> height)
{
	int left = 0;
	int right = height.size() - 1;
	int maxArea = 0;
	while (left != right)
	{
		int area = (right - left) * min(height[left], height[right]);
		if (area > maxArea)
		{
			maxArea = area;
		}
		if (height[left] > height[right])
		{
			right--;
		}
		else
		{
			left++;
		}
	}
	return maxArea;
}


int main()
{
	vector<int> height = { 1,8,6,2,5,4,8,3,7 };

	cout << MaxArea(height);

	return 0;
}