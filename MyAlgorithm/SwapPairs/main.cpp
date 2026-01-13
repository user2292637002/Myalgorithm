#include<iostream>
using namespace std;

struct ListNode
{
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* nextNode) : val(x), next(nextNode) {}
};

class Solution
{
public:
	ListNode* swapPairs(ListNode* head)
	{
		if (head == nullptr || head->next == nullptr)
			return head;
		ListNode* newHead = head->next;
		ListNode* prev = nullptr;
		ListNode* current = head;
		while (current != nullptr && current->next != nullptr)
		{
			ListNode* nextPair = current->next->next;
			ListNode* second = current->next;
			// ½»»»½Úµã
			second->next = current;
			current->next = nextPair;
			if (prev != nullptr)
			{
				prev->next = second;
			}
			prev = current;
			current = nextPair;
		}
		return newHead;
	}

private:

};


ListNode* InitList(int* arr, int n)
{
	if (n <= 0) return nullptr;
	ListNode* head = new ListNode(*arr);
	ListNode* current = head;
	for (int i = 1; i < n; i++)
	{
		ListNode* newNode = new ListNode(*(arr + i));
		current->next = newNode;
		current = newNode;
	}
	return head;
}




int main()
{
	int arr[] = { 1,2,3,4 };
	ListNode* head = InitList(arr, 4);
	Solution sol;
	ListNode* newHead = sol.swapPairs(head);
	while (newHead != nullptr)
	{
		cout << newHead->val << " ";
		newHead = newHead->next;
	}
}