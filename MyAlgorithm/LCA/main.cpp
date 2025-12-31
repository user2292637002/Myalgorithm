#include"btree.h"

int main()
{
	btree bt;
	int* arr = new int[127];
	for(int i=1;i<=127;i++)
	{
		arr[i-1] = i;
	}
	bt.InitTree(arr,127);
	bt.PrintTree();
	delete[] arr;
}