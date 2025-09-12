/*
��Ŀ������
��дһ���������������ǽ�������ַ������� s ��ת��
Ҫ��ԭ���޸��������飬ʹ�� O(1) �Ķ���ռ�����

ʾ����
���룺s = ["h","e","l","l","o"]
�����["o","l","l","e","h"]

���룺s = ["H","a","n","n","a","h"]
�����["h","a","n","n","a","H"]

��ʾ��
ʹ��˫ָ�뼼�ɡ�һ��ָ������鿪ͷ (left) ��ʼ����һ��ָ�������ĩβ (right) ��ʼ����������ָ��ָ���Ԫ�أ�
Ȼ�� left ָ�����ƣ�right ָ�����ƣ�ֱ������������
*/

#include<iostream>
using namespace std;

void ReverseString(string &str);

int main()
{
    string str;
    cin >> str;
    ReverseString(str);
    cout << str;
	return 0;
}

void ReverseString(string &str)
{
    int left = 0;
    int right = str.length() - 1;
    while (left < right)
    {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}