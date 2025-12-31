#include<iostream>
#include"Tree.h"
#include<time.h>
#include<stdlib.h>
using namespace std;


int main()
{
    srand((unsigned)time(nullptr));
    BST tree;
    for (int i = 1; i <= 127; i++)
    {
        tree.Insert(rand() % 100);
        cout << "BalanceFactor: " << tree.GetBalanceFactor()
            << " Height: " << tree.GetHeight() << endl;
    }  
    tree.Print();
	return 0;
}