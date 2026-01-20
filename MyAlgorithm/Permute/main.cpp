#include<iostream>
#include<vector>
#include<functional>

using namespace std;

class Solution
{
public:
	vector<vector<int>> permute(vector<int>& nums)
	{
		vector<vector<int>> result;
		vector<int> current;
		vector<bool> used(nums.size(), false);
		function<void()> backtrack = [&]()
		{
			if (current.size() == nums.size())
			{
				result.push_back(current);
				return;
			}
			for (int i = 0; i < nums.size(); ++i)
			{
				if (used[i]) continue;
				used[i] = true;
				current.push_back(nums[i]);
				backtrack();
				current.pop_back();
				used[i] = false;
			}
		};
		backtrack();
		return result;
	}


};




int main()
{
	vector<int> nums = { 1,2,3 };
	Solution sol;
	vector<vector<int>> permutations = sol.permute(nums);
	for (const auto& perm : permutations)
	{
		for (int num : perm)
		{
			cout << num << " ";
		}
		cout << endl;
	}
	return 0;
}