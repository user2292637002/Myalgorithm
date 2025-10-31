#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;

vector<int> Function(vector<int>& nums, int target)
{
	unordered_map<int, int> num_map;

	for (int i = 0; i < nums.size(); ++i)
	{
		int complement = target - nums[i];
		if (num_map.find(complement) != num_map.end())
		{
			return { num_map[complement], i };
		}
		else
		{
			num_map[nums[i]] = i;
		}
	}
	return {};
}

void main()
{
	vector<int> nums = { 2,7,11,15 };
	int target = 9;
	vector<int> result = Function(nums, target);
	for (int index : result)
	{
		cout << index << " ";
	}
}