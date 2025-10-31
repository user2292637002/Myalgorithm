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
�γ̱�(Course Schedule)
�Ѷȣ� �е�
������
�����ѧ�ڱ���ѡ�� numCourses �ſγ̣���Ϊ 0 �� numCourses - 1��
��ѡ��ĳЩ�γ�֮ǰ��ҪһЩ���޿γ̡� ���޿γ̰����� prerequisites ���������� prerequisites[i] = [ai, bi] ����ʾ���Ҫѧϰ�γ� ai ����ô������ѧϰ�γ� bi ��
���磬��Ҫѧϰ�γ� 0 ������Ҫ����ɿγ� 1 ��������һ����[0, 1] ����ʾ���ǡ�
�����ж��Ƿ����������пγ̵�ѧϰ��������ԣ����� true�����򣬷��� false��
ʾ�� 1��
���룺numCourses = 2, prerequisites = [[1,0]]
�����true
���ͣ��ܹ��� 2 �ſγ̡�ѧϰ�γ� 1 ֮ǰ������Ҫ��ɿγ� 0 �����ǿ��ܵġ�
*/