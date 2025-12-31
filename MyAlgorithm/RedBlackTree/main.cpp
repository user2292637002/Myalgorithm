#include<iostream>
#include"RBTree.h"
using namespace std;

int main()
{
	RBTree tree;
	for(int i = 10; i >= 1; --i)
	{
		tree.insert(i*10);
	}	
	tree.print();
	return 0;
}