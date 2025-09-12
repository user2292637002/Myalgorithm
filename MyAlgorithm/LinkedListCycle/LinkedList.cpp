#include"LinkedList.h"

LinkNode* InitLinkedList(int a[],int n)
{
	LinkNode* head = nullptr;
	LinkNode* tail = nullptr;
	for (int i = 0; i < n; i++)
	{
		LinkNode* newNode = new LinkNode();
		newNode->value = a[i];
		newNode->nextNode = nullptr;
		if (!head)
		{
			head = tail = newNode;
		}
		else
		{
			tail->nextNode = newNode;
			tail = newNode;
		}
	}
	return head;
}

void PrintList(LinkNode* head)
{
	LinkNode* curr = head;

	while (curr)
	{
		cout << curr->value << "->";
		curr = curr->nextNode;
	}
	cout <<"nullptr"<< endl;
}

void DeleteList(LinkNode* head)
{
	while (head)
	{
		LinkNode* node = head;
		head = head->nextNode;
		delete node;
	}
}