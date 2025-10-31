#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;

class Solution
{
public:
	Solution() {};
	~Solution() {};
	bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
	{
		vector<int> indegree(numCourses, 0);
		unordered_map<int, vector<int>> graph;
		for (const auto& pre : prerequisites)
		{
			int course = pre[0];
			int prereq = pre[1];
			graph[prereq].push_back(course);
			indegree[course]++;
		}
		queue<int> q;
		for (int i = 0; i < numCourses; ++i)
		{
			if (indegree[i] == 0)
			{
				q.push(i);
			}
		}
		int completedCourses = 0;
		while (!q.empty())
		{
			int course = q.front();
			q.pop();
			completedCourses++;
			for (int neighbor : graph[course])
			{
				indegree[neighbor]--;
				if (indegree[neighbor] == 0)
				{
					q.push(neighbor);
				}
			}
		}
		return completedCourses == numCourses;
	}

};


int main()
{
	int numCourses = 2;
	vector<vector<int>> prerequisites = { {1,0} };
	Solution sol;
	cout << sol.canFinish(numCourses, prerequisites) << endl;
	return 0;
}


/*
课程表(Course Schedule)
难度： 中等
描述：
你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1。
在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai ，那么必须先学习课程 bi 。
例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个对[0, 1] 来表示它们。
请你判断是否可能完成所有课程的学习？如果可以，返回 true；否则，返回 false。
示例 1：
输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
*/