/**
 * @file Tree.h
 * @brief 二叉搜索树(BST)实现，支持插入、删除、查找、平衡等操作
 */

#pragma once
#include <corecrt_malloc.h>
#include <queue>
#include <stack>
#include <iostream>
using namespace std;

/**
 * @struct BSTNode
 * @brief 二叉搜索树节点结构体
 */
struct  BSTNode
{
	int data;              // 节点存储的数据值
	BSTNode* leftChild;    // 左子节点指针
	BSTNode* rightChild;   // 右子节点指针
	BSTNode* parent;       // 父节点指针
};

/**
 * @class BST
 * @brief 二叉搜索树类，实现基本的BST操作和平衡功能
 * 
 * 特性：
 * - 支持插入、删除、查找操作
 * - 自动维护树的高度和平衡因子
 * - 支持树平衡操作（AVL旋转）
 * - 支持层序遍历打印
 */
class BST
{
private:
	BSTNode* root;         // 根节点指针
	int height;            // 树的高度（从根到最深叶子节点的路径长度）
	float balanceFactor;   // 平衡因子（左右子树节点数不平衡的比例，范围0-1）

	/**
	 * @brief 迭代清除树的所有节点，释放内存（使用栈避免递归栈溢出）
	 * @param node 要清除的根节点
	 */
	void Clear(BSTNode* node)
	{
		if (node == nullptr)
		{
			return;
		}

		stack<BSTNode*> nodeStack;
		nodeStack.push(node);

		while (!nodeStack.empty())
		{
			BSTNode* current = nodeStack.top();
			nodeStack.pop();

			if (current->leftChild != nullptr)
			{
				nodeStack.push(current->leftChild);
			}
			if (current->rightChild != nullptr)
			{
				nodeStack.push(current->rightChild);
			}

			free(current);
		}
	}

	/**
	 * @brief 迭代计算指定节点的高度（使用栈避免递归栈溢出）
	 * @param node 要计算高度的节点
	 * @return 节点的高度（空节点返回-1，叶子节点返回0）
	 */
	int GetHeight(BSTNode* node)
	{
		if (node == nullptr)
		{
			return -1;
		}

		// 使用后序遍历，用栈存储节点和访问状态
		// 状态：0-未访问，1-左子树已访问，2-左右子树都已访问
		stack<BSTNode*> nodeStack;
		stack<int> stateStack;  // 0: 初始, 1: 左子树处理完, 2: 右子树处理完
		stack<int> heightStack; // 存储已计算的高度

		nodeStack.push(node);
		stateStack.push(0);

		while (!nodeStack.empty())
		{
			BSTNode* current = nodeStack.top();
			int state = stateStack.top();

			if (state == 0)
			{
				// 处理左子树
				stateStack.pop();
				stateStack.push(1);
				if (current->leftChild != nullptr)
				{
					nodeStack.push(current->leftChild);
					stateStack.push(0);
				}
			}
			else if (state == 1)
			{
				// 处理右子树
				stateStack.pop();
				stateStack.push(2);
				if (current->rightChild != nullptr)
				{
					nodeStack.push(current->rightChild);
					stateStack.push(0);
				}
			}
			else // state == 2
			{
				// 左右子树都处理完，计算当前节点高度
				nodeStack.pop();
				stateStack.pop();

				int leftHeight = -1;
				int rightHeight = -1;

				// 从heightStack中取出左右子树的高度
				// 由于是后序遍历：先处理左子树，再处理右子树
				// 所以栈顶是右子树高度，然后是左子树高度
				if (current->rightChild != nullptr)
				{
					rightHeight = heightStack.top();
					heightStack.pop();
				}
				if (current->leftChild != nullptr)
				{
					leftHeight = heightStack.top();
					heightStack.pop();
				}

				int currentHeight = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
				heightStack.push(currentHeight);
			}
		}

		return heightStack.top();
	}

	/**
	 * @brief 迭代计算以指定节点为根的子树中的节点总数（使用栈避免递归栈溢出）
	 * @param node 根节点
	 * @return 节点总数（空节点返回0）
	 */
	int GetNodeCount(BSTNode* node)
	{
		if (node == nullptr)
		{
			return 0;
		}

		int count = 0;
		stack<BSTNode*> nodeStack;
		nodeStack.push(node);

		while (!nodeStack.empty())
		{
			BSTNode* current = nodeStack.top();
			nodeStack.pop();
			count++;

			if (current->leftChild != nullptr)
			{
				nodeStack.push(current->leftChild);
			}
			if (current->rightChild != nullptr)
			{
				nodeStack.push(current->rightChild);
			}
		}

		return count;
	}

	/**
	 * @brief 更新整棵树的高度
	 */
	void UpdateHeight()
	{
		height = GetHeight(root);
	}

	/**
	 * @brief 更新平衡因子
	 * 
	 * 平衡因子 = |左子树节点数 - 右子树节点数| / 总节点数
	 * 值越接近1表示树越不平衡，值越接近0表示树越平衡
	 */
	void UpdateBalanceFactor()
	{
		if (root == nullptr)
		{
			balanceFactor = 0.0f;
			return;
		}
		int leftCount = GetNodeCount(root->leftChild);
		int rightCount = GetNodeCount(root->rightChild);
		int totalCount = leftCount + rightCount;
		if (totalCount == 0)
		{
			balanceFactor = 0.0f;
		}
		else
		{
			balanceFactor = (float)abs(leftCount - rightCount) / totalCount;
		}
	}

	/**
	 * @brief 右旋转操作（用于平衡左子树过高的情况）
	 * 
	 * 旋转前：
	 *      node
	 *     /   \
	 *  left    ...
	 *  /   \
	 * ...  leftRight
	 * 
	 * 旋转后：
	 *    left
	 *   /    \
	 * ...    node
	 *       /    \
	 *  leftRight  ...
	 * 
	 * @param node 需要旋转的节点（不平衡的节点）
	 * @return 旋转后新的根节点
	 */
	BSTNode* RotateRight(BSTNode* node)
	{
		BSTNode* leftChild = node->leftChild;
		BSTNode* leftRight = leftChild->rightChild;

		leftChild->rightChild = node;
		leftChild->parent = node->parent;
		node->leftChild = leftRight;
		node->parent = leftChild;

		if (leftRight != nullptr)
		{
			leftRight->parent = node;
		}

		if (leftChild->parent != nullptr)
		{
			if (leftChild->parent->leftChild == node)
			{
				leftChild->parent->leftChild = leftChild;
			}
			else
			{
				leftChild->parent->rightChild = leftChild;
			}
		}
		else
		{
			root = leftChild;
		}

		return leftChild;
	}

	/**
	 * @brief 左旋转操作（用于平衡右子树过高的情况）
	 * 
	 * 旋转前：
	 *  node
	 * /    \
	 * ...  right
	 *     /    \
	 * rightLeft ...
	 * 
	 * 旋转后：
	 *      right
	 *     /    \
	 *  node    ...
	 *  /   \
	 * ... rightLeft
	 * 
	 * @param node 需要旋转的节点（不平衡的节点）
	 * @return 旋转后新的根节点
	 */
	BSTNode* RotateLeft(BSTNode* node)
	{
		BSTNode* rightChild = node->rightChild;
		BSTNode* rightLeft = rightChild->leftChild;

		rightChild->leftChild = node;
		rightChild->parent = node->parent;
		node->rightChild = rightLeft;
		node->parent = rightChild;

		if (rightLeft != nullptr)
		{
			rightLeft->parent = node;
		}

		if (rightChild->parent != nullptr)
		{
			if (rightChild->parent->leftChild == node)
			{
				rightChild->parent->leftChild = rightChild;
			}
			else
			{
				rightChild->parent->rightChild = rightChild;
			}
		}
		else
		{
			root = rightChild;
		}

		return rightChild;
	}

	/**
	 * @brief 左右双旋转（先左旋后右旋）
	 * 
	 * 用于处理左子树的右子树过高的情况
	 * 1. 先对左子节点进行左旋转
	 * 2. 再对当前节点进行右旋转
	 * 
	 * @param node 需要旋转的节点
	 * @return 旋转后新的根节点
	 */
	BSTNode* RotateLeftRight(BSTNode* node)
	{
		node->leftChild = RotateLeft(node->leftChild);
		return RotateRight(node);
	}

	/**
	 * @brief 右左双旋转（先右旋后左旋）
	 * 
	 * 用于处理右子树的左子树过高的情况
	 * 1. 先对右子节点进行右旋转
	 * 2. 再对当前节点进行左旋转
	 * 
	 * @param node 需要旋转的节点
	 * @return 旋转后新的根节点
	 */
	BSTNode* RotateRightLeft(BSTNode* node)
	{
		node->rightChild = RotateRight(node->rightChild);
		return RotateLeft(node);
	}

	/**
	 * @brief 计算节点的平衡因子（高度差）
	 * 
	 * 平衡因子 = 左子树高度 - 右子树高度
	 * - 值 > 1：左子树过高，需要右旋转
	 * - 值 < -1：右子树过高，需要左旋转
	 * - 值在 [-1, 1] 之间：平衡
	 * 
	 * @param node 要计算的节点
	 * @return 平衡因子值
	 */
	int GetBalance(BSTNode* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		return GetHeight(node->leftChild) - GetHeight(node->rightChild);
	}

	/**
	 * @brief 平衡单个节点，根据平衡因子选择相应的旋转操作
	 * 
	 * 判断逻辑：
	 * - 如果左子树过高（balance > 1）：
	 *   - 左子节点的左子树高：单右旋转
	 *   - 左子节点的右子树高：左右双旋转
	 * - 如果右子树过高（balance < -1）：
	 *   - 右子节点的右子树高：单左旋转
	 *   - 右子节点的左子树高：右左双旋转
	 * 
	 * @param node 需要平衡的节点
	 * @return 平衡后的根节点
	 */
	BSTNode* BalanceNode(BSTNode* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		int balance = GetBalance(node);

		// 左子树过高
		if (balance > 1)
		{
			if (GetBalance(node->leftChild) >= 0)
			{
				return RotateRight(node);
			}
			else
			{
				return RotateLeftRight(node);
			}
		}
		// 右子树过高
		else if (balance < -1)
		{
			if (GetBalance(node->rightChild) <= 0)
			{
				return RotateLeft(node);
			}
			else
			{
				return RotateRightLeft(node);
			}
		}

		return node;
	}

	/**
	 * @brief 迭代平衡整棵树（使用栈避免递归栈溢出）
	 * 
	 * 采用后序遍历方式，从叶子节点向上平衡每个节点
	 * 确保在平衡父节点时，子节点已经平衡
	 * 
	 * @param node 要处理的根节点
	 */
	void BalanceRecursive(BSTNode* node)
	{
		if (node == nullptr)
		{
			return;
		}

		// 使用栈进行后序遍历
		stack<BSTNode*> nodeStack;
		stack<int> stateStack;  // 0: 初始, 1: 左子树处理完, 2: 左右子树都已处理

		nodeStack.push(node);
		stateStack.push(0);

		while (!nodeStack.empty())
		{
			BSTNode* current = nodeStack.top();
			int state = stateStack.top();

			if (state == 0)
			{
				// 处理左子树
				stateStack.pop();
				stateStack.push(1);
				if (current->leftChild != nullptr)
				{
					nodeStack.push(current->leftChild);
					stateStack.push(0);
				}
			}
			else if (state == 1)
			{
				// 处理右子树
				stateStack.pop();
				stateStack.push(2);
				if (current->rightChild != nullptr)
				{
					nodeStack.push(current->rightChild);
					stateStack.push(0);
				}
			}
			else // state == 2
			{
				// 左右子树都处理完，平衡当前节点
				nodeStack.pop();
				stateStack.pop();
				BalanceNode(current);
			}
		}
	}

public:
	/**
	 * @brief 构造函数，初始化空的二叉搜索树
	 */
	BST()
	{
		root = nullptr;
		height = 0;
		balanceFactor = 0.0;
	}

	/**
	 * @brief 析构函数，释放所有节点内存
	 */
	~BST()
	{
		Clear(root);
	}

	/**
	 * @brief 向树中插入一个新值
	 * 
	 * 插入规则：
	 * - 如果值小于当前节点，插入左子树
	 * - 如果值大于当前节点，插入右子树
	 * - 如果值已存在，不进行插入
	 * 
	 * 插入后自动更新树的高度和平衡因子
	 * 
	 * @param value 要插入的整数值
	 */
	void Insert(int value)
	{
		if (root == nullptr)
		{
			root = (BSTNode*)malloc(sizeof(BSTNode));
			root->data = value;
			root->leftChild = nullptr;
			root->rightChild = nullptr;
			root->parent = nullptr;
			UpdateHeight();
			UpdateBalanceFactor();
			return;
		}

		BSTNode* current = root;
		while (true)
		{
			if (value < current->data)
			{
				if (current->leftChild == nullptr)
				{
					current->leftChild = (BSTNode*)malloc(sizeof(BSTNode));
					current->leftChild->data = value;
					current->leftChild->leftChild = nullptr;
					current->leftChild->rightChild = nullptr;
					current->leftChild->parent = current;
					break;
				}
				current = current->leftChild;
			}
			else if (value > current->data)
			{
				if (current->rightChild == nullptr)
				{
					current->rightChild = (BSTNode*)malloc(sizeof(BSTNode));
					current->rightChild->data = value;
					current->rightChild->leftChild = nullptr;
					current->rightChild->rightChild = nullptr;
					current->rightChild->parent = current;
					break;
				}
				current = current->rightChild;
			}
			else
			{
				// 值已存在，不插入
				return;
			}
		}
		UpdateHeight();
		UpdateBalanceFactor();
		BalanceRecursive(root);
	}

	/**
	 * @brief 从树中删除指定值
	 * 
	 * 删除策略：
	 * 1. 叶子节点：直接删除
	 * 2. 只有一个子节点：用子节点替换当前节点
	 * 3. 有两个子节点：用右子树的最小值（中序遍历后继）替换当前节点值，然后删除后继节点
	 * 
	 * 删除后自动更新树的高度和平衡因子
	 * 
	 * @param value 要删除的整数值
	 * @return true 如果成功删除，false 如果值不存在
	 */
	bool Remove(int value)
	{
		if (root == nullptr)
		{
			return false;
		}

		BSTNode* current = root;
		while (current != nullptr)
		{
			// 向左子树查找
			if (value < current->data)
			{
				current = current->leftChild;
			}
			else if (value > current->data) // 向右子树查找
			{
				current = current->rightChild;
			}
			else // 找到该值，删除该节点
			{
				// 情况1：叶子节点（无子节点）
				if (current->leftChild == nullptr && current->rightChild == nullptr)
				{
					if (current->parent == nullptr) // 根节点
					{
						root = nullptr;
					}
					else if (current->parent->leftChild == current)
					{
						current->parent->leftChild = nullptr;
					}
					else
					{
						current->parent->rightChild = nullptr;
					}
					free(current);
					UpdateHeight();
					UpdateBalanceFactor();
					return true;
				}
				// 情况2：只有右子节点
				else if (current->leftChild == nullptr)
				{
					if (current->parent == nullptr) // 根节点
					{
						root = current->rightChild;
						if (root != nullptr)
						{
							root->parent = nullptr;
						}
					}
					else if (current->parent->leftChild == current)
					{
						current->parent->leftChild = current->rightChild;
						if (current->rightChild != nullptr)
						{
							current->rightChild->parent = current->parent;
						}
					}
					else
					{
						current->parent->rightChild = current->rightChild;
						if (current->rightChild != nullptr)
						{
							current->rightChild->parent = current->parent;
						}
					}
					free(current);
					UpdateHeight();
					UpdateBalanceFactor();
					return true;
				}
				// 情况3：只有左子节点
				else if (current->rightChild == nullptr)
				{
					if (current->parent == nullptr) // 根节点
					{
						root = current->leftChild;
						if (root != nullptr)
						{
							root->parent = nullptr;
						}
					}
					else if (current->parent->leftChild == current)
					{
						current->parent->leftChild = current->leftChild;
						if (current->leftChild != nullptr)
						{
							current->leftChild->parent = current->parent;
						}
					}
					else
					{
						current->parent->rightChild = current->leftChild;
						if (current->leftChild != nullptr)
						{
							current->leftChild->parent = current->parent;
						}
					}
					free(current);
					UpdateHeight();
					UpdateBalanceFactor();
					return true;
				}
				// 情况4：有两个子节点，用右子树的最小值（中序遍历后继）替换
				else
				{
					BSTNode* successor = current->rightChild;
					while (successor->leftChild != nullptr)
					{
						successor = successor->leftChild;
					}
					
					current->data = successor->data;
					
					// 删除 successor 节点
					if (successor->parent->leftChild == successor)
					{
						successor->parent->leftChild = successor->rightChild;
					}
					else
					{
						successor->parent->rightChild = successor->rightChild;
					}
					
					if (successor->rightChild != nullptr)
					{
						successor->rightChild->parent = successor->parent;
					}
					
					free(successor);
					UpdateHeight();
					UpdateBalanceFactor();
					return true;
				}
			}
		}
		UpdateHeight();
		UpdateBalanceFactor();
		return false;
	}

	/**
	 * @brief 在树中查找指定值
	 * 
	 * 查找过程：
	 * - 从根节点开始
	 * - 如果值小于当前节点，在左子树中查找
	 * - 如果值大于当前节点，在右子树中查找
	 * - 如果值等于当前节点，返回true
	 * - 如果到达空节点，返回false
	 * 
	 * 时间复杂度：O(log n) 平均情况，O(n) 最坏情况（退化为链表）
	 * 
	 * @param value 要查找的整数值
	 * @return true 如果找到，false 如果不存在
	 */
	bool Find(int value)
	{
		BSTNode* current = root;
		while (current != nullptr)
		{
			if (value == current->data)
			{
				return true;
			}
			else if (value < current->data)
			{
				current = current->leftChild;
			}
			else
			{
				current = current->rightChild;
			}
		}
		return false;
	}	

	/**
	 * @brief 层序遍历打印树的所有节点值
	 * 
	 * 使用队列实现广度优先搜索（BFS）
	 * 按从上到下、从左到右的顺序打印节点值
	 * 
	 * 示例输出：根节点 左子节点 右子节点 ...
	 */
	void Print()
	{
		if (root == nullptr)
		{
			return;
		}
		
		queue<BSTNode*> q;
		q.push(root);
		while (!q.empty())
		{
			BSTNode* current = q.front();
			q.pop();
			cout << current->data << " ";
			if (current->leftChild != nullptr)
			{
				q.push(current->leftChild);
			}
			if (current->rightChild != nullptr)
			{
				q.push(current->rightChild);
			}
		}
		cout << endl;
	}

	/**
	 * @brief 平衡整棵树
	 * 
	 * 当平衡因子超过阈值（0.7）时，执行平衡操作
	 * 使用AVL树的旋转策略来重新平衡树结构
	 * 
	 * 平衡过程：
	 * 1. 更新树的高度和平衡因子
	 * 2. 如果平衡因子 > 0.7，递归平衡所有节点
	 * 3. 重复步骤1-2，直到平衡因子 <= 0.7
	 * 
	 * 注意：这是一个迭代过程，可能需要多次旋转才能完全平衡
	 */
	void Balance()
	{
		UpdateHeight();
		UpdateBalanceFactor();
		
		// 如果平衡因子超过阈值，进行平衡操作
		while (balanceFactor > 0.3f)
		{
			BalanceRecursive(root);
			UpdateHeight();
			UpdateBalanceFactor();
		}
	}

	/**
	 * @brief 获取树的高度
	 * @return 树的高度（从根到最深叶子节点的路径长度，空树返回0）
	 */
	int GetHeight() const
	{
		return height;
	}

	/**
	 * @brief 获取树的平衡因子
	 * @return 平衡因子值（范围0-1，0表示完全平衡，1表示完全不平衡）
	 */
	float GetBalanceFactor() const
	{
		return balanceFactor;
	}

};
