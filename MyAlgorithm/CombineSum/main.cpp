#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class Solution
{
private:


public:
    /// @brief 找到所有可以使数字和为目标值的组合
    /// @param candidates 候选数字数组（可能有重复）
    /// @param target 目标值
    /// @return 所有符合条件的组合
    /// 
    /// 给定一个候选人编号的集合 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

    /// candidates 中的每个数字在每个组合中只能使用 一次 。
    /// 注意：解集不能包含重复的组合。 
    /// 
    /// 示例 1:
    /// 输入: candidates = [10,1,2,7,6,1,5], target = 8,
    /// 输出:
    /// [
    /// [1,1,6],
    /// [1,2,5],
    /// [1,7],
    /// [2,6]
    /// ]
    /// 示例 2:
    /// 输入: candidates = [2,5,2,1,2], target = 5,
    /// 输出:
    /// [
    /// [1,2,2],
    /// [5]
    /// ]
    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
    {
        vector<vector<int>> res;
        vector<int> path;

        // 排序数组，便于去重和剪枝
        sort(candidates.begin(), candidates.end());

        // 开始回溯
        backtrack(candidates, target, 0, path, res);
        return res;
    }

private:
    /// @brief 回溯函数
    /// @param candidates 候选数字数组（已排序）
    /// @param target 剩余目标值
    /// @param start 起始位置（确保每个下标只使用一次）
    /// @param path 当前路径（当前组合的值）
    /// @param res 结果集合
    void backtrack(vector<int>& candidates, int target, int start,
        vector<int>& path, vector<vector<int>>& res)
    {
        // 如果目标值等于 0，说明找到了一个有效组合
        if (target == 0)
        {
            res.push_back(path);
            return;
        }

        // 从 start 位置开始遍历候选数字
        for (int i = start; i < candidates.size(); i++)
        {
            // 剪枝：如果当前数字已经大于 target，后面的数字也会大于，提前结束
            if (candidates[i] > target)
            {
                break;
            }

            // 去重：避免生成重复的组合
            // 关键：在同一层递归中（i > start），如果当前数字和前一个数字相同，
            // 那么跳过当前数字，避免生成重复的组合
            // 
            // 例如：[1,1,2], target=3
            // - 第一层：i=0, start=0, 选择第一个1，递归到下一层
            //   - 第二层：i=1, start=1, 可以选择第二个1（因为 i == start，不是 i > start）
            // - 第一层：i=1, start=0, 此时 i > start 且 candidates[1]==candidates[0]，跳过
            //   这样可以避免生成重复的组合，因为选择第一个1和第二个1会产生相同的组合
            if (i > start && candidates[i] == candidates[i - 1])
            {
                continue;
            }

            // 选择当前数字（按下标 i）
            path.push_back(candidates[i]);

            // 递归：从下一个位置开始（i+1），确保每个下标只使用一次
            backtrack(candidates, target - candidates[i], i + 1, path, res);

            // 回溯：撤销选择
            path.pop_back();
        }
    }
};





int main()
{
    Solution sol;
    // 测试用例1：与示例1一致
    vector<int> candidates = { 10,1,2,7,6,1,5 };
    vector<vector<int>> result = sol.combinationSum(candidates, 8);

    cout << "测试用例1: candidates = [10,1,2,7,6,1,5], target = 8" << endl;
    cout << "输出:" << endl;
    for (vector<int> vec : result)
    {
        cout << "[";
        for (int i = 0; i < vec.size(); i++)
        {
            cout << vec[i];
            if (i < vec.size() - 1) cout << ",";
        }
        cout << "]" << endl;
    }

    // 测试用例2：与示例2一致
    cout << "\n测试用例2: candidates = [2,5,2,1,2], target = 5" << endl;
    vector<int> candidates2 = { 2,5,2,1,2 };
    vector<vector<int>> result2 = sol.combinationSum(candidates2, 5);
    cout << "输出:" << endl;
    for (vector<int> vec : result2)
    {
        cout << "[";
        for (int i = 0; i < vec.size(); i++)
        {
            cout << vec[i];
            if (i < vec.size() - 1) cout << ",";
        }
        cout << "]" << endl;
    }

    return 0;
}





