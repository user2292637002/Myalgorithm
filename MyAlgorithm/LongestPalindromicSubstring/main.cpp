/*
��Ŀ����������һ���ַ��� s���ҵ� s ����Ļ����Ӵ���
������ڶ��������ͬ��������Ӵ������ص�һ����

ʾ����
����: s = "babad"
���: "bab"
����: "aba" Ҳ��һ����Ч�𰸡�

����: s = "cbbd"
���: "bb"


��ʾ��
ʹ��������չ�� (Expand Around Centers)��

���Ĵ������Ŀ�����һ���ַ����������ȣ���Ҳ�����������ַ�֮�䣨ż�����ȣ���
�����ַ����е�ÿһ�����ܵ����ĵ㣨�� 2n-1 ����n �����ַ����ģ�n-1 ��˫�ַ����ģ���
����ÿ�����ģ���������չ��ֱ���ַ�������Ȼ򵽴�߽硣
��¼��չ����������������Ĵ�����ʼλ�úͳ��ȡ�

*/



#include<iostream>
#include<string>
using namespace std;


string LongestPalindrome(string s);

void ExpandAroundCenter(const string& s, int left, int right, int& start, int& maxLength);

int main()
{
	string str;
	cin >> str;
	cout << LongestPalindrome(str) << endl;
	return 0;
}


string LongestPalindrome(string s)
{
	if (s.empty()) return "";

	int start = 0; //���ڼ�¼��ʼλ��
	int maxLength = 1; //���ڼ�¼����

	// �������п��ܵ�����λ��
	for (int i = 0; i < s.length(); i++)
	{
		// ������ s[i] Ϊ���ĵ��������Ȼ���
		ExpandAroundCenter(s, i, i, start, maxLength);

		// ������ s[i] �� s[i+1] ֮��ļ�϶Ϊ���ĵ�ż�����Ȼ���
		ExpandAroundCenter(s, i, i + 1, start, maxLength);
	}

	return s.substr(start, maxLength);
}

// ������ (left, right) ��������չ
void ExpandAroundCenter(const string& s, int left, int right, int& start, int& maxLength)
{
	// �ڱ߽������ַ����ʱ��չ
	while (left >= 0 && right < s.length() && s[left] == s[right])
	{
		int currentLength = right - left + 1;
		if (currentLength > maxLength)
		{
			maxLength = currentLength;
			start = left;
		}
		--left;
		++right;
	}
}