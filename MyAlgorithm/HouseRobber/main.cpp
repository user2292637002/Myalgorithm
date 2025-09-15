/*
��Ŀ������
����һ��רҵ��С͵���ƻ�͵���ؽֵķ��ݡ�ÿ�䷿�ڲ���һ�����ֽ𣬵�����͵���������䷿���ᴥ����������
�������� nums����������͵������߽�

ʾ����
���룺nums = [1,2,3,1]
�����4
���ͣ�͵�� 1 �͵� 3 �䷿����� = 1 + 3 = 4��

��ʾ��
dp[i] ��ʾ͵���� i �䷿ʱ������
״̬ת�ƣ�dp[i] = max(dp[i-1], dp[i-2] + nums[i])
������͵��ǰ����dp[i-1]�� vs ͵��ǰ����dp[i-2] + nums[i]��

*/

#include<iostream>
#include<vector>>
#include<algorithm>
using namespace std;

int MaxEarning(vector<int> money)
{
	if (money.empty()) return 0;
	if (money.size() == 1) return 0;

	int n = money.size();

	int prev2 = 0;
	int prev1 = money[0];
	int maxEarn = 0;
	for (int i = 1; i < n; i++)
	{
		maxEarn = max(prev1, prev2 + money[i]);
		prev2 = prev1;
		prev1 = maxEarn;
	}
	return maxEarn;
}


int main()
{
	vector<int> money = {1,2,3,1};
	cout << MaxEarning(money) << endl;

	return 0;
}