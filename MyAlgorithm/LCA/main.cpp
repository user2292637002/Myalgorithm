#include"btree.h"
#include<unordered_map>
#include<iostream>
using namespace std;

/// @brief 查找两个节点的最近公共祖先（LCA）
/// @param root 当前子树的根节点
/// @param p 第一个节点
/// @param q 第二个节点
/// @return 返回最近公共祖先节点，如果不存在则返回nullptr
template<typename T>
btnode<T>* LCA(btnode<T> *root, btnode<T> *p, btnode<T> *q)
{
	if(root == nullptr || root == p || root == q)
		return root;
	btnode<T> *left = LCA(root->left, p, q);
	btnode<T> *right = LCA(root->right, p, q);
	if(left != nullptr && right != nullptr)
		return root;
	if(left != nullptr)
		return left;
	return right;
}


/// @brief 深度优先搜索，统计路径和等于target的路径数量
/// @param node 当前节点
/// @param currSum 当前路径的前缀和
/// @param target 目标路径和
/// @param prefix 前缀和到出现次数的映射
/// @return 返回以当前节点为终点的满足条件的路径数量
int dfs(btnode<int>* node, long currSum, int target, unordered_map<long, int>& prefix)
{
	if (!node)
		return 0;

	currSum += node->data;
	int res = prefix[currSum - target];  // 查找是否存在前缀和等于currSum-target的路径

	prefix[currSum]++;  // 将当前前缀和加入映射
	res += dfs(node->left, currSum, target, prefix);
	res += dfs(node->right, currSum, target, prefix);
	prefix[currSum]--;  // 回溯，移除当前前缀和

	return res;
}

/// @brief 统计二叉树中路径和等于target的路径数量
/// @param root 树的根节点
/// @param target 目标路径和
/// @return 返回满足条件的路径数量
int pathSum(btnode<int>* root, int target)
{
	unordered_map<long, int> prefix;
	prefix[0] = 1; // 初始化前缀和为0的路径数量为1（空路径）
	return dfs(root, 0, target, prefix);
}


int main()
{
	// 手动构建测试树
	//       10
	//      /  \
	//     5   -3
	//    / \    \
	//   3   2   11
	btnode<int> root;
	root.data = 10;
	root.left = nullptr;   // 初始化指针
	root.right = nullptr;
	root.parent = nullptr;
	
	btnode<int> node1;
	node1.data = 5;
	node1.left = nullptr;  // 初始化指针
	node1.right = nullptr;
	node1.parent = &root;
	
	btnode<int> node2;
	node2.data = -3;
	node2.left = nullptr;  // 初始化指针
	node2.right = nullptr;
	node2.parent = &root;
	
	root.left = &node1;
	root.right = &node2;
	
	btnode<int> node3;
	node3.data = 3;
	node3.left = nullptr;  // 初始化指针
	node3.right = nullptr;
	node3.parent = &node1;
	node1.left = &node3;
	
	btnode<int> node4;
	node4.data = 2;
	node4.left = nullptr;  // 初始化指针
	node4.right = nullptr;
	node4.parent = &node1;
	node1.right = &node4;
	
	btnode<int> node5;
	node5.data = 11;
	node5.left = nullptr;  // 初始化指针
	node5.right = nullptr;
	node5.parent = &node2;
	node2.right = &node5;
	
	// 测试：查找路径和等于8的路径数量
	cout << pathSum(&root, 8) << endl;
	return 0;
}