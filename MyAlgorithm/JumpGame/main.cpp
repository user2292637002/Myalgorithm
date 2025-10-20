/*
题目描述：
给定一个非负整数数组 nums，你最初位于数组的第一个下标。数组中的每个元素表示你在该位置可以跳跃的最大长度。
判断你是否能够到达最后一个下标。

示例：
输入: nums = [2,3,1,1,4]
输出: true
解释: 可以先跳 1 步，从下标 0 到达下标 1，然后从下标 1 跳 3 步到达最后一个下标。

提示：
维护一个变量 maxReach，表示当前能到达的最远位置。
遍历数组，如果 i > maxReach，说明无法到达位置 i，返回 false。
否则更新 maxReach = max(maxReach, i + nums[i])。
如果 maxReach >= n-1，返回 true。
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool canJump(const vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return true;          // 空或只有一个元素必定能到

    int maxReach = 0;                 // 当前能到达的最远位置
    for (int i = 0; i < n; ++i) {
        if (i > maxReach) return false;    // 到不了 i
        maxReach = max(maxReach, i + nums[i]);
        if (maxReach >= n - 1) return true; // 提前退出
    }
    return true;
}

int main() {
    vector<int> nums = { 2, 3, 1, 1, 4 };
    cout << boolalpha << canJump(nums) << endl;   // true
    return 0;
}