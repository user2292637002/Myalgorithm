#include<iostream>
#include<vector>
using namespace std;


// 暴力解法 时间复杂度O(n^2) 空间复杂度O(1)
int maxArea(const vector<int>& height)
{
	int maxArea = 0;
	
	for (int i = 0; i < height.size(); i++)
	{
		int minHeight = height[i];
		for(int j=i;j<height.size();j++)
		{
			if (height[j] < minHeight)
			{
				minHeight = height[j];
			}
			int area = minHeight * (j - i + 1);
			if(area > maxArea)
				maxArea = area;
		}
	}
	return maxArea;
}



int main()
{
	vector<int> height = { 2,1,5,6,2,3 };
	cout << maxArea(height) << endl;
	return 0;
}