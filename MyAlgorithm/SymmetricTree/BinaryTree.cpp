#include"BinaryTree.h"

/**
 * @brief 根据层序字符串创建二叉树
 *
 * 约定：
 * 1. 输入字符串按层序（广度优先）顺序给出节点值；
 * 2. 用 INT_MIN（通常取 -2147483648）表示空指针；
 * 3. 遇到 INT_MIN 即跳过，不再为其创建 TreeNode；
 * 4. 返回构建好的根指针，若首字符就是 INT_MIN 则返回 nullptr。
 *
 * @param line 空格分隔的层序序列，例如 "1 2 3 -2147483648 -2147483648 4 5"
 * @return TreeNode* 构建后的根节点指针
 */
TreeNode* CreateBinaryTree_LevelOrder(const std::string& line) {
    /* ---- 1. 解析第一个值，若不存在或为空树标志则直接返回 ---- */
    stringstream ss(line); // 把字符串当成输入流
    int val;
    if (!(ss >> val) || val == INT_MIN) return nullptr;

    /* ---- 2. 创建根节点并放入队列，准备广度优先构建 ---- */
    TreeNode* root = new TreeNode(val); // 根节点
    queue<TreeNode*> q;            // 辅助队列，存放待处理节点
    q.push(root);                       // 初始只有根节点

    /* ---- 3. 按层序循环：每次取出队首节点，尝试给其挂左右孩子 ---- */
    while (!q.empty()) {
        TreeNode* cur = q.front(); // 当前要“挂孩子”的节点
        q.pop();

        /* ---- 3.1 处理左孩子 ---- */
        if (ss >> val && val != INT_MIN) {           // 读到有效值
            cur->leftChild = new TreeNode(val);      // 新建左孩子
            q.push(cur->leftChild);                  // 左孩子入队，后续给它挂孙子
        }
        // 若读到 INT_MIN 或没有更多值，cur->leftChild 保持 nullptr

        /* ---- 3.2 处理右孩子（逻辑同左孩子） ---- */
        if (ss >> val && val != INT_MIN) {
            cur->rightChild = new TreeNode(val);
            q.push(cur->rightChild);
        }
    } // end while

    /* ---- 4. 返回构建好的根指针 ---- */
    return root;
}


/**
 * @brief 以前序区间 [pl..pr] 与中序区间 [il..ir] 构建子树
 *
 * 前提：pre 与 in 均无重复元素
 *
 * @param pre     前序遍历数组
 * @param pl      当前子树在前序中的左端下标
 * @param pr      当前子树在前序中的右端下标
 * @param in      中序遍历数组
 * @param il      当前子树在中序中的左端下标
 * @param ir      当前子树在中序中的右端下标
 * @param inMap   中序值→下标的哈希表，用于 O(1) 找到根位置
 * @return TreeNode* 当前子树的根节点指针
 */
TreeNode* buildPI(const int pre[], int pl, int pr,
    const int in[], int il, int ir,
    unordered_map<int, int>& inMap)
{
    /* 1. 区间为空，返回空子树 */
    if (pl > pr) return nullptr;

    /* 2. 前序第一个元素就是当前子树的根 */
    int rootVal = pre[pl];
    TreeNode* node = new TreeNode(rootVal);

    /* 3. 在中序里找到根的位置 k，把中序切成左右两棵子树 */
    int k = inMap[rootVal];      // 根在中序中的下标
    int leftSize = k - il;       // 左子树节点个数

    /* 4. 递归构建左子树
       前序：跳过根，取 leftSize 个元素  [pl+1 .. pl+leftSize]
       中序：左半段                         [il .. k-1]        */
    node->leftChild = buildPI(pre, pl + 1, pl + leftSize,
        in, il, k - 1, inMap);

    /* 5. 递归构建右子树
       前序：剩下的元素                     [pl+leftSize+1 .. pr]
       中序：右半段                         [k+1 .. ir]        */
    node->rightChild = buildPI(pre, pl + leftSize + 1, pr,
        in, k + 1, ir, inMap);

    /* 6. 返回当前子树的根，供上一层接指针 */
    return node;
}

/**
 * @brief 用户友好接口：以前序和中序构建整棵二叉树
 *
 * @param pre 前序遍历数组，长度 n
 * @param in  中序遍历数组，长度 n
 * @param n   数组长度（节点个数）
 * @return TreeNode* 树根指针，空树返回 nullptr
 */
TreeNode* CreateBinaryTree_PreIn(const int pre[], const int in[], int n)
{
    /* 0. 特判空树 */
    if (n == 0) return nullptr;

    /* 1. 先把中序值→下标存进哈希表，后面每次查找 O(1) */
    unordered_map<int, int> inMap;
    for (int i = 0; i < n; ++i) inMap[in[i]] = i;

    /* 2. 调用递归辅助，初始区间为整棵树的范围 */
    return buildPI(pre, 0, n - 1, in, 0, n - 1, inMap);
}


TreeNode* CreateBinaryTree_PostIn(const int post[], const int in[], int n)
{

}
