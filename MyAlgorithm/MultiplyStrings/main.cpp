#include<iostream>
using namespace std;


// �ַ�����ˣ����Բο��ֹ��˷��Ĺ��̣��Ӹ�λ��ʼ��λ��ˣ���������ۼӵ���Ӧ��λ���ϣ����Ա���������ʱ��������⡣
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
				// ������λ����ˣ��˻������λ��
				int mul = (num1[i] - '0') * (num2[j] - '0');
				// ʮλ�͸�λ���±�
				// ʮλ
				int p1 = i + j;
				// ��λ
				int p2 = i + j + 1;
				int sum = mul + pos[p2];

				// �ۼӵ���Ӧλ��
				// ��λ��ģ��10��ȡ�ø�λ
				pos[p2] = sum % 10;
				// ʮλ������ʮ�����Ͻ�λ
				pos[p1] += sum / 10;
			}
		}

		// �������ַ���
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