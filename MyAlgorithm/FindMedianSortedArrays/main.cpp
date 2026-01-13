#include<iostream>
#include<vector>
using namespace std;

class Solution
{
public:
    double findMedianSortedArrays(const vector<int>& nums1, const vector<int>& nums2)
    {
        vector<int> mege;
        int i = 0, j = 0;
        while (i < nums1.size() && j < nums2.size())
        {
            if (nums1[i] < nums2[j])
            {
                mege.push_back(nums1[i]);
                ++i;
            }
            else
            {
                mege.push_back(nums2[j]);
                ++j;
            }
        }
        while (i < nums1.size())
        {
            mege.push_back(nums1[i]);
            ++i;
        }
        while (j < nums2.size())
        {
            mege.push_back(nums2[j]);
            ++j;
        }
        int size = mege.size();
        for (int i = 0; i < size; i++)
        {
            cout << " " << mege[i];
        }
        if (size % 2)
        {
            return (double)mege[(size + 1) / 2];
        }
        else
        {
            return ((double)mege[size / 2] + (double)mege[size / 2 - 1]);
        }
    }
	Solution();
	~Solution();
};

Solution::Solution()
{
}

Solution::~Solution()
{
}

int main()
{
    Solution s;
    vector<int> nums1 = { 1,3 };
    vector<int> nums2 = { 2 };
    cout<<s.findMedianSortedArrays(nums1, nums2);

	return 0;
}