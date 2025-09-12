/*题目一：两数之和
题目描述：
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target 的那 两个 整数，并返回它们的数组下标。
你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
你可以按任意顺序返回答案。

示例：
输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。

输入：nums = [3,2,4], target = 6
输出：[1,2]

输入：nums = [3,3], target = 6
输出：[0,1]


提示：
尝试使用哈希表来优化查找效率。对于数组中的每个元素 nums[i]，我们想知道是否存在一个元素 nums[j]，使得 nums[i] + nums[j] = target。
这等价于 nums[j] = target - nums[i]。我们可以用哈希表存储已经遍历过的元素及其索引。
*/

#include <iostream>
#include <vector>
#include <unordered_map> 
using namespace std;

vector<int> twoSum(const vector<int>& nums, int target);

int main() {    
    vector<int> nums;
    int n, target;
    cout << "请输入数组大小: ";
    cin >> n;
    cout << "请输入 " << n << " 个数字: ";
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }
    cout << "请输入目标值: ";
    cin >> target;
    
    vector<int> result = twoSum(nums, target);

    cout << "输出: [";
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}


vector<int> twoSum(const vector<int>& nums, int target) {
    unordered_map<int, int> numToIndex;
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];   
        if (numToIndex.find(complement) != numToIndex.end()) {
            return { numToIndex[complement], i };
        }
        numToIndex[nums[i]] = i;
    }
    return {};
}