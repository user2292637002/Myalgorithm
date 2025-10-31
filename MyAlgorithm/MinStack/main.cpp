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
题目五：最小栈 (Min Stack)
难度： 中等
描述：
设计一个支持 push，pop，top 操作，并能在常数时间内检索到最小元素的栈。

push(x) —— 将元素 x 推入栈中。
pop() —— 删除栈顶的元素。
top() —— 获取栈顶元素。
getMin() —— 检索栈中的最小元素。
示例：
输入：
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

输出：
[null,null,null,null,-3,null,0,-2]

解释：
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // 返回 -3
minStack.pop();
minStack.top();    // 返回 0
minStack.getMin(); // 返回 -2
*/