#include<iostream>
#include<stack>
#include<unordered_map>
using namespace std;

class  Solution
{
public:
	Solution() {};
	~Solution() {};
	bool isValid(string s)
	{
		for (char c : s)
		{
			if (pairs.count(c))
			{
				data.push(c);
			}
			else
			{
				if(data.empty() || pairs.at(data.top()) != c)
					return false;
				data.pop();
			}
		}
		return data.empty();
	}
private:
	stack<char> data;
	unordered_map<char, char> pairs = { {'[', ']'},{'{','}'},{'(',')'} };
};



int main()
{
	string str1 = "{[()]}";
	string str2 = "[{()}]";
	string str3 = "{[[(())]]}}";
	Solution sol;
	cout << sol.isValid(str1) << endl;
	cout << sol.isValid(str2) << endl;
	cout << sol.isValid(str3) << endl;
	return 0;
}