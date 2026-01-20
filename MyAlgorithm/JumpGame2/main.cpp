#include<iostream>
#include<vector>
using namespace std;

class Solution
{
public:
	int jump(vector<int>& nums)
	{
		int steps = 0;          // 跳跃次数
		int maxReach = 0;      // 当前能到达的最远位置
		int edge = 0;          // 当前跳跃的边界位置
		for (int i = 0; i < nums.size() - 1; ++i)
		{
			// 更新能到达的最远位置
			maxReach = max(maxReach, i + nums[i]);
			// 到达当前跳跃的边界，进行下一次跳跃
			if (i == edge)
			{
				steps++;
				edge = maxReach;
				// 提前退出：如果已经能到达或超过最后一个位置
				if (edge >= nums.size() - 1)
				{
					break;
				}
			}
		}
		return steps;
	}

};



int main()
{
	return 0;
}