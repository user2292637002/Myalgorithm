/*
题目描述：
编写一个函数，其作用是将输入的字符串数组 s 反转。
要求原地修改输入数组，使用 O(1) 的额外空间解决。

示例：
输入：s = ["h","e","l","l","o"]
输出：["o","l","l","e","h"]

输入：s = ["H","a","n","n","a","h"]
输出：["h","a","n","n","a","H"]

提示：
使用双指针技巧。一个指针从数组开头 (left) 开始，另一个指针从数组末尾 (right) 开始，交换两个指针指向的元素，
然后 left 指针右移，right 指针左移，直到它们相遇。
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