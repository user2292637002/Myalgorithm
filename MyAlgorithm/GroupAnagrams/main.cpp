#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

class Solution
{
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs)
	{
		unordered_map<string, vector<string>> anagramMap;
		for (string& str : strs)
		{
			string sortedStr = str; 
			sort(sortedStr.begin(), sortedStr.end());
			anagramMap[sortedStr].push_back(str);
		}

		vector<vector<string>> result;
		for (auto& pair : anagramMap)
		{
			result.push_back(move(pair.second));
		}
		return result;
	}

};




int main()
{
	
	return 0;
}