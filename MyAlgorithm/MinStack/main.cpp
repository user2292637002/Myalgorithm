#include<iostream>
#include<stack>
#include<vector>
using namespace std;

struct  MinStack
{
	stack<int> data;
	stack<int> mins;
	MinStack() {}

	void push(int val)
	{
		data.push(val);
		if (!mins.empty())
		{
			if(data.top() <= mins.top())
				mins.push(val);
			else
				mins.push(mins.top());
		}
		else
		{
			mins.push(val);
		}
	}
	
	void pop()
	{
		data.pop();
		mins.pop();
	}

	int top()
	{
		return data.top();
	}

	int getMin()
	{
		return mins.top();
	}
	

};



int main()
{
	MinStack ms;
	int n;
	for(int i = 0; i < 5; i++)
	{
		cin >> n;
		ms.push(n);
	}

	for (int  i = 0; i <5; i++)
	{
		cout << "current min:" << ms.getMin() << endl;
		ms.pop();
	}
}

/*
��Ŀ�壺��Сջ (Min Stack)
�Ѷȣ� �е�
������
���һ��֧�� push��pop��top �����������ڳ���ʱ���ڼ�������СԪ�ص�ջ��

push(x) ���� ��Ԫ�� x ����ջ�С�
pop() ���� ɾ��ջ����Ԫ�ء�
top() ���� ��ȡջ��Ԫ�ء�
getMin() ���� ����ջ�е���СԪ�ء�
ʾ����
���룺
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

�����
[null,null,null,null,-3,null,0,-2]

���ͣ�
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // ���� -3
minStack.pop();
minStack.top();    // ���� 0
minStack.getMin(); // ���� -2
*/