/*
题目描述：
整数数组 nums 按升序排列，数组在某个未知下标 k 处进行了旋转（例如 [0,1,2,4,5,6,7] 变成 [4,5,6,7,0,1,2]）。
给定目标值 target，如果数组中存在这个目标值，则返回它的下标，否则返回 -1。

示例：
输入: nums = [4,5,6,7,0,1,2], target = 0
输出: 4

提示：
旋转数组可以分为两段有序部分。
判断 mid 在哪一段，再判断 target 是否在有序的那一段中。

*/

#include<iostream>
#include<vector>
using namespace std;


int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;

        // 判断左半段是否有序
        if (nums[left] <= nums[mid]) {
            if (target >= nums[left] && target < nums[mid]) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        // 右半段有序
        else {
            if (target > nums[mid] && target <= nums[right]) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
    }
    return -1;
}


int main()
{
    vector<int> nums = { 4,5,6,7,0,1,2 };
    int target = 0;
    cout << search(nums, target);
	return 0;
}