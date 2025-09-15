/*
��Ŀ������
���� cost ��ʾÿ��̨�׵Ļ��ѣ�����Դӵ� 0 ����� 1 ����ʼ��ÿ�ο����� 1 �� 2 ����
����¥�ݶ��������������һ��̨�ף�ʱֹͣ������С���ѡ�

ʾ����
���룺cost = [10, 15, 20]
�����15
���ͣ����±�Ϊ 1 ��̨�׿�ʼ������ 15�����������������ܻ��� 15��

��ʾ��
dp[i] ��ʾ����� i ��̨�׵���С���ѡ�
״̬ת�ƣ�dp[i] = min(dp[i-1], dp[i-2]) + cost[i]
���մ��� min(dp[n-1], dp[n-2])����Ϊ���Դ������������������

*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int MinCostClimbStairs(vector<int> cost)
{
	int n = cost.size();
	if (n <= 1)
		return 0;
	

	int prev2 = cost[0];
	int prev1 = cost[1];
	int minCost = 0;
	for (int i = 2; i <= n; i++)
	{
		int currentCost = (i == n) ? 0 : cost[i];
		minCost = min(prev2, prev1) + currentCost;
		prev2 = prev1;
		prev1 = minCost;
	}
	return minCost;
}


int main()
{
	vector<int> cost = { 10,15,20 };

	cout << MinCostClimbStairs(cost) << endl;
	return 0;
}