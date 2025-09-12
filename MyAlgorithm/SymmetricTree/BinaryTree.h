#pragma once
#include <queue>
#include <climits>
#include <sstream>
#include <iostream>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int value;
    TreeNode* leftChild;
    TreeNode* rightChild;
    explicit TreeNode(int v = 0)
        : value(v), leftChild(nullptr), rightChild(nullptr) {
    }
};


TreeNode* CreateBinaryTree_LevelOrder(const std::string& line);


TreeNode* buildPI(const int pre[], int pl, int pr,
    const int in[], int il, int ir,
    std::unordered_map<int, int>& inMap);

TreeNode* CreateBinaryTree_PreIn(const int pre[], const int in[], int n);


TreeNode* CreateBinaryTree_PostIn(const int post[], const int in[], int n);