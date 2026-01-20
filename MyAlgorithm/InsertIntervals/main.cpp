#include<iostream>
#include<vector>
using namespace std;

class Solution
{
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval)
    {
        for (auto& interval : intervals)
        {
            if (interval[1] < newInterval[0] || interval[0] > newInterval[1])
            {
                continue;
            }
            else
            {
                newInterval[0] = min(newInterval[0], interval[0]);
                newInterval[1] = max(newInterval[1], interval[1]);
                interval[0] = -1;
                interval[1] = -1;
            }
        }
        vector<vector<int>> result;
        bool inserted = false;
        for (auto& interval : intervals)
        {
            if (interval[0] == -1 && interval[1] == -1)
            {
                continue;
            }
            if (!inserted && newInterval[0] < interval[0])
            {
                result.push_back(newInterval);
                inserted = true;
            }
            result.push_back(interval);
        }
        if (!inserted)
        {
            result.push_back(newInterval);
        }
        return result;
    }

};

int main()
{
    Solution sol;
    vector<vector<int>> intervals = { {1,2},{3,5},{6,7},{8,10},{12,16} };
    vector<int> newInterval = { 4,8 };
    sol.insert(intervals, newInterval);
    return 0;
}