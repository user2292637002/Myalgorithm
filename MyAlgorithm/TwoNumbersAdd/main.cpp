#include<iostream>
#include"solution.h"
using namespace std;

/// @brief 两数相加：将两个用链表表示的非负整数相加
/// 链表中的数字按逆序存储，每个节点存储一位数字
class Solution
{
public:
	/// @brief 将两个链表表示的数字相加
	/// @param l1 第一个数字的链表（逆序）
	/// @param l2 第二个数字的链表（逆序）
	/// @return 返回表示结果的链表（逆序）
	/// 
	/// 算法思路：直接逐位相加，处理进位，避免整数溢出
	/// 时间复杂度：O(max(m,n))，空间复杂度：O(max(m,n))
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
	{
		ListNode* dummy = new ListNode(0);  // 虚拟头节点，简化代码
		ListNode* curr = dummy;
		int carry = 0;  // 进位
		
		// 同时遍历两个链表，逐位相加
		while (l1 != nullptr || l2 != nullptr || carry != 0)
		{
			int sum = carry;
			
			// 如果 l1 还有节点，加上其值
			if (l1 != nullptr)
			{
				sum += l1->val;
				l1 = l1->next;
			}
			
			// 如果 l2 还有节点，加上其值
			if (l2 != nullptr)
			{
				sum += l2->val;
				l2 = l2->next;
			}
			
			// 计算当前位的值和进位
			carry = sum / 10;
			curr->next = new ListNode(sum % 10);
			curr = curr->next;
		}
		
		ListNode* result = dummy->next;
		delete dummy;  // 删除虚拟头节点
		return result;
	}
};

/// @brief 辅助函数：创建链表
/// @param arr 数组
/// @param n 数组长度
/// @return 返回链表头节点
ListNode* createList(int arr[], int n)
{
	if (n == 0)
		return nullptr;
	
	ListNode* head = new ListNode(arr[0]);
	ListNode* curr = head;
	for (int i = 1; i < n; i++)
	{
		curr->next = new ListNode(arr[i]);
		curr = curr->next;
	}
	return head;
}

/// @brief 辅助函数：打印链表
/// @param head 链表头节点
void printList(ListNode* head)
{
	while (head != nullptr)
	{
		cout << head->val;
		if (head->next != nullptr)
			cout << " -> ";
		head = head->next;
	}
	cout << endl;
}

/// @brief 辅助函数：释放链表内存
/// @param head 链表头节点
void deleteList(ListNode* head)
{
	while (head != nullptr)
	{
		ListNode* temp = head;
		head = head->next;
		delete temp;
	}
}

int main()
{
	Solution solution;
	
	// 测试用例1：342 + 465 = 807
	// l1: 2 -> 4 -> 3 (表示 342)
	// l2: 5 -> 6 -> 4 (表示 465)
	// 结果: 7 -> 0 -> 8 (表示 807)
	int arr1[] = {2, 4, 3};
	int arr2[] = {5, 6, 4};
	ListNode* l1 = createList(arr1, 3);
	ListNode* l2 = createList(arr2, 3);
	
	cout << "测试用例1:" << endl;
	cout << "l1: ";
	printList(l1);
	cout << "l2: ";
	printList(l2);
	
	ListNode* result1 = solution.addTwoNumbers(l1, l2);
	cout << "结果: ";
	printList(result1);
	cout << endl;
	
	// 清理内存
	deleteList(l1);
	deleteList(l2);
	deleteList(result1);
	
	// 测试用例2：0 + 0 = 0
	ListNode* l3 = new ListNode(0);
	ListNode* l4 = new ListNode(0);
	
	cout << "测试用例2:" << endl;
	cout << "l1: ";
	printList(l3);
	cout << "l2: ";
	printList(l4);
	
	ListNode* result2 = solution.addTwoNumbers(l3, l4);
	cout << "结果: ";
	printList(result2);
	cout << endl;
	
	// 清理内存
	deleteList(l3);
	deleteList(l4);
	deleteList(result2);
	
	// 测试用例3：999 + 9 = 1008
	// l1: 9 -> 9 -> 9 (表示 999)
	// l2: 9 (表示 9)
	// 结果: 8 -> 0 -> 0 -> 1 (表示 1008)
	int arr3[] = {9, 9, 9};
	int arr4[] = {9};
	ListNode* l5 = createList(arr3, 3);
	ListNode* l6 = createList(arr4, 1);
	
	cout << "测试用例3:" << endl;
	cout << "l1: ";
	printList(l5);
	cout << "l2: ";
	printList(l6);
	
	ListNode* result3 = solution.addTwoNumbers(l5, l6);
	cout << "结果: ";
	printList(result3);
	
	// 清理内存
	deleteList(l5);
	deleteList(l6);
	deleteList(result3);
	
	return 0;
}
