#include<iostream>
using namespace std;

struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* nextNode) : val(x), next(nextNode) {}
};


ListNode* InitList(int* arr, int n)
{
	if (n <= 0)
		return nullptr;
	ListNode* head = new ListNode(*arr);
	ListNode* current = head;
	for (int i = 1; i < n; ++i)
	{
		ListNode* newNode = new ListNode(*(arr + i));
		current->next = newNode;
		current = newNode;
	}
	return head;
}

ListNode* ReverseList(ListNode* head)
{
	ListNode* prev = nullptr;
	ListNode* current = head;
	while (current != nullptr)
	{
		ListNode* nextTemp = current->next;
		current->next = prev;
		prev = current;
		current = nextTemp;
	}
	return prev;
}

int main()
{
	int a[] = { 1,2,3,4,5 };
	ListNode* head = InitList(a, 5);
	ListNode* reversedHead = ReverseList(head);
	ListNode* current = reversedHead;
	while (current != nullptr)
	{
		cout << current->val << " ";
		current = current->next;
	}
	return 0;
}
