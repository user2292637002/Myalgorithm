#include<iostream>
#include"MyVector.h"
using namespace std;

int main()
{
	MyVector<int> a;
	for (int i = 0; i < 5; ++i) a.push_back(i);
	MyVector<int> b(a);          // 拷贝构造
	b.push_back(99);
	for (size_t i = 0; i < b.size(); ++i) std::cout << b[i] << ' ';
}