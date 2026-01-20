#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class Solution
{
public:
    /// @brief 找到所有 words 串联子串的起始位置（滑动窗口优化）
        /// @param s 主字符串
        /// @param words 单词数组
        /// @return 所有符合条件的子串起始位置
        /// 
        /// 算法思路：滑动窗口 + 哈希表
        /// 1. 由于单词必须对齐，需要从不同的起始偏移量开始（0 到 wordLength-1）
        /// 2. 对每个起始偏移量，使用滑动窗口维护当前窗口内的单词计数
        /// 3. 窗口右边界每次移动一个单词长度，添加新单词
        /// 4. 如果新单词导致某个单词超量，左边界收缩直到不超量
        /// 5. 如果窗口大小正好等于所需长度且没有超量，记录起始位置
        ///
        /// 时间复杂度：O(n * wordLength)，其中 n 是 s 的长度
        /// 空间复杂度：O(m)，用于存储单词计数
    vector<int> findSubstrings(string s, vector<string>& words)
    {
        int word_len = words[0].size(); // 一个单词的长度
        int window_len = word_len * words.size(); // 所有单词的总长度，即窗口大小

        // 目标：窗口中的单词出现次数必须与 target_cnt 完全一致
        unordered_map<string, int> target_cnt;
        for (auto& w : words) {
            target_cnt[w]++;
        }

        vector<int> ans;
        // 枚举第一个窗口的左端点，做 word_len 次起点不同的滑动窗口
        for (int start = 0; start < word_len; start++) {
            unordered_map<string, int> cnt;
            int overload = 0; // 统计过多的单词个数（包括不在 words 中的单词）
            // 枚举窗口最后一个单词的右开端点
            for (int right = start + word_len; right <= s.size(); right += word_len) {
                // 1. in_word 进入窗口
                string in_word = s.substr(right - word_len, word_len);
                // 下面 cnt[in_word]++ 后，in_word 的出现次数过多
                if (cnt[in_word] == target_cnt[in_word]) {
                    overload++;
                }
                cnt[in_word]++;

                int left = right - window_len; // 窗口第一个单词的左端点
                if (left < 0) { // 窗口大小不足 window_len
                    continue;
                }

                // 2. 更新答案
                // 如果没有超出 target_cnt 的单词，那么也不会有少于 target_cnt 的单词
                if (overload == 0) {
                    ans.push_back(left);
                }

                // 3. 窗口最左边的单词 out_word 离开窗口，为下一轮循环做准备
                string out_word = s.substr(left, word_len);
                cnt[out_word]--;
                if (cnt[out_word] == target_cnt[out_word]) {
                    overload--;
                }
            }
        }
        return ans;
    }

private:

};




int main()
{
    string s = "barfoofoobarthefoobarman";
    vector<string> words = { "bar","foo","the" };
    Solution sol;
    vector<int> result = sol.findSubstrings(s, words);
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}