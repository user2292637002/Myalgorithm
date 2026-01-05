#include<iostream>
#include<vector>
#include<stack>
using namespace std;


// 暴力解法 时间复杂度O(n^2) 空间复杂度O(1)
vector<int> Solution(const vector<int>& temperatures)
{
    vector<int> result;
    for(int i=0; i<temperatures.size()-1;i++)
    {
        int count = 0;
        for(int j=i+1;j<temperatures.size();j++)
        {
            if(temperatures[j] > temperatures[i])
            {
                count = j - i;
                break;
            }
        }
        result.push_back(count);
    }
    result.push_back(0);
    return result;
}

// 单调栈解法 时间复杂度O(n) 空间复杂度O(n)
vector<int> Solution2(const vector<int>& temperatures)
{
    vector<int> result;
    stack<int> s;
    for(int i=0; i<temperatures.size();i++)
    {
        while(!s.empty()&&temperatures[i] > temperatures[s.top()])
        {
            result.push_back(i - s.top());
            s.pop();
        }
        s.push(i);
    }
    while(!s.empty())
    {
        result.push_back(0);
        s.pop();
    }
    return result;
}

int main()
{
    vector<int> temperatures = { 73,74,75,71,69,72,76,73 };
    vector<int> result = Solution2(temperatures);
    for(int i=0; i<result.size();i++)
    {
        cout << result[i] << " ";
    }

	return 0;
}