#pragma once
#include <corecrt_malloc.h>
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

/// @brief 二叉树节点结构体
/// 包含左右子节点指针和父节点指针，用于构建带父节点指针的二叉树
struct btnode
{
    int data;       // 节点数据
	btnode* left;   // 左子节点指针
	btnode* right;  // 右子节点指针
	btnode* parent; // 父节点指针
}; 

/// @brief 二叉树类
/// 实现了一个带父节点指针的二叉树，支持层序遍历初始化
class  btree
{
private:
	btnode* root;           // 根节点指针
	void Clear(btnode* node); // 递归清理节点内存的辅助函数
    int height;             // 树的高度（成员变量，但当前未使用）
public:
	btree();                // 构造函数，初始化根节点
	~ btree();              // 析构函数，释放所有节点内存
    /// @brief 层序遍历初始化树
    /// @param arr 节点数据数组
    /// @param n 节点总个数（包括根节点）
    /// 按照层序遍历的顺序从左到右、从上到下创建节点
    void InitTree(int *arr,int n);
    /// @brief 获取树的高度
    /// @return 返回树的高度
    int GetHeight();
    /// @brief 层序遍历打印树
    /// 按照层序遍历的顺序从左到右、从上到下打印树
    /// 先打印根节点，然后打印左子节点，再打印右子节点
    /// 直到打印完所有节点
    void PrintTree();
};

/// @brief 构造函数
/// 初始化根节点指针为空
btree:: btree()
{
	root = nullptr;
}

/// @brief 析构函数
/// 释放整棵树的所有节点内存
btree::~ btree()
{
    Clear(root);      // 清理所有节点
    root = nullptr;   // 将根节点指针置空
}

/// @brief 清理节点内存的辅助函数
/// @param node 要清理的子树根节点
/// 使用栈进行非递归的后序遍历，释放所有节点内存
void btree::Clear(btnode* node)
{
	if(node == nullptr)
        return;
    stack<btnode*> s;  // 使用栈进行非递归遍历
    s.push(node);      // 将根节点入栈
    while (!s.empty())
    {
        btnode* curr = s.top();
        s.pop();
        // 先处理右子树，再处理左子树（因为栈是后进先出）
        if(curr->right != nullptr)
            s.push(curr->right);
        if(curr->left != nullptr)
            s.push(curr->left);
        free(curr);    // 释放当前节点内存
    }
}

/// @brief 层序遍历初始化树
/// @param arr 节点数据数组
/// @param n 节点总个数（包括根节点）
/// 按照层序遍历的顺序从左到右、从上到下创建节点
/// 使用队列维护层序遍历的顺序，确保正确构建完全二叉树
void btree::InitTree(int* arr,int n)
{
    // 参数检查
    if(arr == nullptr || n <= 0)
        return;
    
    // 如果树已存在，先清空
    if(root != nullptr)
    {
        Clear(root);
        root = nullptr;
    }
    
    // 创建根节点
    root = (btnode*)malloc(sizeof(btnode));
    if(root == nullptr)  // 内存分配失败检查
        return;
    root->left = nullptr;
    root->right = nullptr;
    root->parent = nullptr;
    root->data = arr[0];
    
    // 使用队列进行层序遍历构建
    queue<btnode*> q;
    q.push(root);
    
    // 从第二个节点开始（索引1）创建子节点
    for(int i = 1; i < n; i++)
    {
        btnode* curr = q.front();
        
        // 优先创建左子节点
        if(curr->left == nullptr)
        {
            btnode* newNode = (btnode*)malloc(sizeof(btnode));
            if(newNode == nullptr)  // 内存分配失败检查
                break;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->data = arr[i];
            newNode->parent = curr;
            curr->left = newNode;
            q.push(newNode);  // 将新节点加入队列，用于后续创建其子节点
        }
        // 如果左子节点已存在，创建右子节点
        else if(curr->right == nullptr)
        {
            btnode* newNode = (btnode*)malloc(sizeof(btnode));
            if(newNode == nullptr)  // 内存分配失败检查
                break;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->data = arr[i];
            newNode->parent = curr;
            curr->right = newNode;
            q.push(newNode);  // 将新节点加入队列，用于后续创建其子节点
            q.pop();  // 当前节点的左右子节点都已创建，从队列中移除
        }
    }
}

/// @brief 获取树的高度
/// @return 返回树的高度（根节点高度为1）
/// 因为创建树时是层序遍历，且是从左到右创建，所以左子树一定比右子树高或相等
/// 只需沿着左子树路径计算高度即可
int btree::GetHeight()
{
    if(root == nullptr)
        return 0;
    btnode* curr = root;
    int height = 1;  // 根节点高度为1
    // 沿着左子树路径向下遍历，计算树的高度
    while (curr != nullptr)
    {
        if(curr->left != nullptr)
        {
            curr = curr->left;
            height++;
        }
        else
        {
            break;  // 到达最底层，退出循环
        }
    }
    return height;
}

/// @brief 层序遍历打印树
/// 按照层序遍历的顺序从左到右、从上到下打印所有节点的数据
void btree::PrintTree()
{
    if(root == nullptr)
    {
        return;
    }
    queue<btnode*> q;
    q.push(root);
    while(!q.empty())
    { 
        btnode* curr = q.front();
        q.pop();
        cout << curr->data << " ";
        // 将子节点加入队列，保持层序遍历顺序
        if(curr->left != nullptr)
            q.push(curr->left);
        if(curr->right != nullptr)
            q.push(curr->right);
    }
    cout << endl;  // 打印完成后换行
}
