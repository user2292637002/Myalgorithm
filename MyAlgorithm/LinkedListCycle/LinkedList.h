#pragma once
#include <iostream>
using namespace std;


struct LinkNode
{
public:
    int value;
    LinkNode* nextNode; 
    LinkNode(int value = 0) :value(value), nextNode(nullptr){}
};

LinkNode* InitLinkedList(int a[],int n);

void PrintList(LinkNode* head);

void DeleteList(LinkNode* head);
