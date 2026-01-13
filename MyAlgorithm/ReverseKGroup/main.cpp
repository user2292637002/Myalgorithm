#include<iostream>
using namespace std;

// 链表节点结构体
struct ListNode
{
	int val;              // 节点存储的值
	ListNode* next;       // 指向下一个节点的指针
	ListNode() : val(0), next(nullptr) {}                                    // 默认构造函数
	ListNode(int x) : val(x), next(nullptr) {}                              // 带值构造函数
	ListNode(int x, ListNode* nextNode) : val(x), next(nextNode) {}          // 带值和下一个节点的构造函数
};


class Solution
{
public:
	// K 个一组翻转链表
	// 题目：给你链表的头节点 head，每 k 个节点一组进行翻转，请你返回修改后的链表
	// 例如：k=2, 链表 1->2->3->4->5 变为 2->1->4->3->5
	// 如果节点总数不是 k 的整数倍，最后剩余的节点保持原有顺序
	//
	// 算法思路：
	// 1. 使用虚拟头节点简化边界处理
	// 2. 每次检查是否有 k 个节点可以翻转（从 prevGroupEnd 开始往后数 k 个节点）
	// 3. 如果有，则翻转这 k 个节点，并连接到前面的链表
	// 4. 更新 prevGroupEnd 指向当前组翻转后的末尾（即原组的第一节点）
	// 5. 重复步骤 2-4，直到剩余节点不足 k 个
	//
	// 时间复杂度：O(n)，其中 n 是链表长度，每个节点最多被访问两次
	// 空间复杂度：O(1)，只使用了常数额外空间
	ListNode* reverseKGroup(ListNode* head, int k)
	{
		// 边界情况：链表为空或 k <= 1，直接返回原链表
		if (head == nullptr || k <= 1)
			return head;
		
		// 创建虚拟头节点，简化边界处理（特别是处理链表头部的翻转）
		ListNode* dummy = new ListNode(0);
		dummy->next = head;
		
		// prevGroupEnd 指向前一组的末尾节点（初始为虚拟头节点）
		// 用于连接翻转后的组
		ListNode* prevGroupEnd = dummy;
		
		while (true)
		{
			// 步骤1：检查是否有 k 个节点可以翻转
			// 从 prevGroupEnd 开始，往后移动 k 步，找到第 k 个节点
			ListNode* kthNode = prevGroupEnd;
			for (int i = 0; i < k && kthNode != nullptr; i++)
			{
				kthNode = kthNode->next;
			}
			
			// 如果 kthNode 为空，说明剩余节点不足 k 个，无需翻转，直接结束
			if (kthNode == nullptr)
				break;
			
			// 步骤2：记录当前组的起始节点和下一组的起始节点
			ListNode* groupStart = prevGroupEnd->next;  // 当前组第一个节点（翻转后将成为最后一个）
			ListNode* nextGroupStart = kthNode->next;   // 下一组的起始节点（用于连接翻转后的链表）
			
			// 步骤3：翻转当前组的 k 个节点
			// 翻转思路：使用三指针法翻转链表
			// prev 指向已翻转部分的头节点（初始为下一组的起始节点，这样翻转后自然连接）
			// current 指向当前要翻转的节点（从组的第一节点开始）
			// 翻转结束后，prev 指向翻转后的头节点（即原组的第 k 个节点）
			ListNode* prev = nextGroupStart;  // 翻转后，当前组的最后一个节点应该指向 nextGroupStart
			ListNode* current = groupStart;   // 从当前组的第一个节点开始翻转
			
			// 翻转当前组：每次翻转一个节点，直到翻转完 k 个节点
			while (current != nextGroupStart)
			{
				ListNode* temp = current->next;  // 保存下一个节点，避免丢失
				current->next = prev;            // 将当前节点的 next 指向前一个节点（翻转）
				prev = current;                   // 更新 prev 为当前节点（已翻转部分的头节点）
				current = temp;                   // 更新 current 为下一个要翻转的节点
			}
			// 翻转完成后，prev 指向翻转后的头节点（原组的第 k 个节点，即 kthNode）
			
			// 步骤4：将翻转后的组连接到前面的链表
			prevGroupEnd->next = kthNode;  // 前一组末尾连接翻转后组的头节点（kthNode）
			
			// 步骤5：更新 prevGroupEnd 为当前组翻转后的末尾节点
			// groupStart 是原组的第一个节点，翻转后成为最后一个节点
			prevGroupEnd = groupStart;
		}
		
		// 返回新的头节点（跳过虚拟头节点）
		ListNode* result = dummy->next;
		delete dummy;  // 释放虚拟头节点
		return result;
	}

private:

};



// 辅助函数：创建链表
ListNode* createList(int arr[], int n)
{
	if (n <= 0) return nullptr;
	ListNode* head = new ListNode(arr[0]);
	ListNode* current = head;
	for (int i = 1; i < n; i++)
	{
		current->next = new ListNode(arr[i]);
		current = current->next;
	}
	return head;
}

// 辅助函数：打印链表
void printList(ListNode* head)
{
	ListNode* current = head;
	while (current != nullptr)
	{
		cout << current->val;
		if (current->next != nullptr)
			cout << "->";
		current = current->next;
	}
	cout << endl;
}

int main()
{
	// 测试用例：链表 1->2->3->4->5，k=2
	// 预期结果：2->1->4->3->5
	int arr[] = { 1, 2, 3, 4, 5 };
	int n = sizeof(arr) / sizeof(arr[0]);
	
	ListNode* head = createList(arr, n);
	
	cout << "原链表: ";
	printList(head);
	
	Solution sol;
	int k = 2;
	ListNode* result = sol.reverseKGroup(head, k);
	
	cout << "k = " << k << " 翻转后: ";
	printList(result);
	
	// 测试用例2：链表 1->2->3->4->5，k=3
	// 预期结果：3->2->1->4->5（最后两个节点不足 k 个，保持不变）
	cout << "\n测试用例2: k=3" << endl;
	int arr2[] = { 1, 2, 3, 4, 5 };
	ListNode* head2 = createList(arr2, n);
	
	cout << "原链表: ";
	printList(head2);
	
	int k2 = 3;
	ListNode* result2 = sol.reverseKGroup(head2, k2);
	
	cout << "k = " << k2 << " 翻转后: ";
	printList(result2);
	
	return 0;
}
