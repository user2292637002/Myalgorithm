#pragma once
#include<vector>
#include<iostream>
#include<string>

using namespace std;

void getNext(int*next,const string& pattern)
{
	int m = pattern.size();
	next[0] = -1;
	int j = 0;
	int k = -1;
	while (j < m - 1)
	{
		if (k == -1 || pattern[j] == pattern[k])
		{
			j++;
			k++;
			next[j] = k;
		}
		else
		{
			k = next[k];
		}
	}
}

int kmp(const string&str,const string& pattern)
{
	int n = str.size();
	int m = pattern.size();
	int* next = new int[m];
	getNext(next, pattern);
	int i = 0; // str 指针
	int j = 0; // pattern 指针
	while (i < n && j < m)
	{
		if (j == -1 || str[i] == pattern[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}
	delete[] next;
	if (j == m)
		return i - j; // 匹配成功，返回起始索引
	else
		return -1;    // 匹配失败
}