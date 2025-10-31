#include<iostream>
using namespace std;


// 字符串相乘，可以参考手工乘法的过程，从个位开始逐位相乘，并将结果累加到对应的位置上，可以避免大数相乘时的溢出问题。
class Solution
{	
public:
	Solution() {};
	~Solution() {};
	string MutiplyStrings(string num1,string num2)
	{
		if (num1 == "0" || num2 == "0") return "0";

		int m = num1.size();
		int n = num2.size();

		int* pos = new int[m + n]();
		for (int i = m - 1; i >= 0; --i)
		{
			for (int j = n - 1; j >= 0; --j)
			{
				// 两个个位数相乘，乘积最多两位数
				int mul = (num1[i] - '0') * (num2[j] - '0');
				// 十位和个位的下标
				// 十位
				int p1 = i + j;
				// 个位
				int p2 = i + j + 1;
				int sum = mul + pos[p2];

				// 累加到对应位置
				// 个位，模以10，取得个位
				pos[p2] = sum % 10;
				// 十位，除以十，加上进位
				pos[p1] += sum / 10;
			}
		}

		// 构造结果字符串
		string result;
		for(int i=0; i < m + n; ++i)
		{
			if (!(result.empty() && pos[i] == 0))
			{
				result.push_back(pos[i] + '0');
			}
		}

		return result.empty() ? "0" : result;
	}
};



int main()
{
	string num1 = "123";
	string num2 = "456";

	Solution sol;
	cout << sol.MutiplyStrings(num1, num2) << endl;

	return 0;
}