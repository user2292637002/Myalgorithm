#include<iostream>
#include<vector>
using namespace std;

class Solution
{
public:
	void rotate(vector<vector<int>>& matrix)
	{
		int n = matrix.size();
		// 先转置矩阵
		for (int i = 0; i < n; ++i)
		{
			for (int j = i + 1; j < n; ++j)
			{
				swap(matrix[i][j], matrix[j][i]);
			}
		}
		// 再水平翻转矩阵
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n / 2; ++j)
			{
				swap(matrix[i][j], matrix[i][n - 1 - j]);
			}
		}
	}

};



int main()
{
	
	return 0;
}