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
	
	void pop_min()
	{
		data.pop();
		mins.pop();
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
		cout << "current min:" << ms.mins.top() << endl;
		ms.pop_min();
	}
}