/**
 * @file RBTree.h
 * @brief 红黑树（Red-Black Tree）实现
 * 
 * 红黑树性质：
 * 1. 每个节点要么是红色，要么是黑色
 * 2. 根节点是黑色
 * 3. 每个叶子节点（NIL）是黑色
 * 4. 如果一个节点是红色，则它的两个子节点都是黑色
 * 5. 从任意节点到其每个叶子的所有路径都包含相同数目的黑色节点
 */

#pragma once
#include <iostream>
using namespace std;

enum Color
{
    RED,
    BLACK
};

/**
 * @struct RBTreeNode
 * @brief 红黑树节点结构
 */
struct  RBTreeNode
{   
    int value;              // 节点值
    RBTreeNode* left;       // 左子节点
    RBTreeNode* right;      // 右子节点
    RBTreeNode* parent;     // 父节点
    Color color;            // 节点颜色

    RBTreeNode(int value) : value(value), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};


/**
 * @class RBTree
 * @brief 红黑树类
 * 
 * 使用哨兵节点（nil）简化边界条件处理
 * 所有叶子节点都指向同一个nil节点
 */
class RBTree
{
private:
    RBTreeNode* root;  // 根节点
    RBTreeNode* nil;   // 哨兵节点（NIL节点）

    /**
     * @brief 递归删除所有节点
     */
    void clear(RBTreeNode* node) {
        if (node != nil && node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    /**
     * @brief 构造函数，初始化空的红黑树
     */
    RBTree() {
        nil = new RBTreeNode(0);
        nil->color = BLACK;
        nil->left = nullptr;
        nil->right = nullptr;
        root = nil;
    }

    /**
     * @brief 析构函数，释放所有节点内存
     */
    ~RBTree() {
        clear(root);
        delete nil;
    }
    /**
     * @brief 搜索指定值的节点
     * @param value 要搜索的值
     * @return 找到的节点指针，如果不存在返回nil
     */
    RBTreeNode* search(int value) {
        RBTreeNode* node = root;
        while (node != nil) {
            if (node->value == value) {
                return node;
            }
            else if (value < node->value) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
        return nil;
    }

    /**
     * @brief 插入新值到红黑树
     * @param value 要插入的值
     */
    void insert(int value) {
        RBTreeNode* node = new RBTreeNode(value);
        node->left = nil;
        node->right = nil;
        insert(node);
    }

    /**
     * @brief 插入节点到红黑树
     * @param node 要插入的节点
     */
    void insert(RBTreeNode* node) {
        RBTreeNode* parent = nil;
        RBTreeNode* current = root;
        
        // 找到插入位置
        while (current != nil) {
            parent = current;
            if (node->value < current->value) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        
        // 设置节点的父节点
        node->parent = parent;
        
        // 插入到树中
        if (parent == nil) {
            root = node;
        }
        else if (node->value < parent->value) {
            parent->left = node;
        }
        else {
            parent->right = node;
        }
        
        // 修复红黑树性质
        fixInsert(node);
    }
    /**
     * @brief 删除指定值的节点
     * @param value 要删除的值
     */
    void remove(int value) {
        RBTreeNode* node = search(value);
        if (node != nil) {
            remove(node);
        }
    }

    /**
     * @brief 获取子树中的最小节点
     * @param node 子树根节点
     * @return 最小节点
     */
    RBTreeNode* minimum(RBTreeNode* node) {
        while (node->left != nil) {
            node = node->left;
        }
        return node;
    }

    /**
     * @brief 用另一个节点替换当前节点
     * @param u 被替换的节点
     * @param v 替换节点（可以是nil）
     */
    void transplant(RBTreeNode* u, RBTreeNode* v) {
        if (u->parent == nil) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        if (v != nil) {
            v->parent = u->parent;
        }
    }

    /**
     * @brief 删除节点
     * @param node 要删除的节点
     */
    void remove(RBTreeNode* node) {
        if (node == nil) {
            return;
        }
        
        RBTreeNode* y = node;
        RBTreeNode* x = nil;
        Color yOriginalColor = y->color;
        
        if (node->left == nil) {
            // 只有右子树或没有子树
            x = node->right;
            transplant(node, node->right);
        }
        else if (node->right == nil) {
            // 只有左子树
            x = node->left;
            transplant(node, node->left);
        }
        else {
            // 有两个子树，用右子树的最小值替换
            y = minimum(node->right);
            yOriginalColor = y->color;
            x = y->right;
            
            if (y->parent == node) {
                x->parent = y;
            }
            else {
                transplant(y, y->right);
                y->right = node->right;
                y->right->parent = y;
            }
            
            transplant(node, y);
            y->left = node->left;
            y->left->parent = y;
            y->color = node->color;
        }
        
        delete node;
        
        // 如果删除的是黑色节点，需要修复红黑树性质
        if (yOriginalColor == BLACK) {
            fixRemove(x);
        }
    }
    /**
     * @brief 左旋转
     * @param node 旋转的支点节点
     */
    void leftRotate(RBTreeNode* node) {
        RBTreeNode* rightChild = node->right;
        node->right = rightChild->left;
        
        if (rightChild->left != nil) {
            rightChild->left->parent = node;
        }
        
        rightChild->parent = node->parent;
        
        if (node->parent == nil) {
            root = rightChild;
        }
        else if (node == node->parent->left) {
            node->parent->left = rightChild;
        }
        else {
            node->parent->right = rightChild;
        }
        
        rightChild->left = node;
        node->parent = rightChild;
    }

    /**
     * @brief 右旋转
     * @param node 旋转的支点节点
     */
    void rightRotate(RBTreeNode* node) {
        RBTreeNode* leftChild = node->left;
        node->left = leftChild->right;
        
        if (leftChild->right != nil) {
            leftChild->right->parent = node;
        }
        
        leftChild->parent = node->parent;
        
        if (node->parent == nil) {
            root = leftChild;
        }
        else if (node == node->parent->left) {
            node->parent->left = leftChild;
        }
        else {
            node->parent->right = leftChild;
        }
        
        leftChild->right = node;
        node->parent = leftChild;
    }

    /**
     * @brief 修复插入后的红黑树性质
     * @param node 新插入的节点
     */
    void fixInsert(RBTreeNode* node) {
        while (node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                // 父节点是祖父节点的左子节点
                RBTreeNode* uncle = node->parent->parent->right;
                
                if (uncle->color == RED) {
                    // 情况1：叔节点是红色，重新着色
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else {
                    // 情况2和3：叔节点是黑色
                    if (node == node->parent->right) {
                        // 情况2：节点是父节点的右子节点，先左旋转
                        node = node->parent;
                        leftRotate(node);
                    }
                    // 情况3：节点是父节点的左子节点，重新着色并右旋转
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rightRotate(node->parent->parent);
                }
            }
            else {
                // 父节点是祖父节点的右子节点（对称情况）
                RBTreeNode* uncle = node->parent->parent->left;
                
                if (uncle->color == RED) {
                    // 情况1：叔节点是红色，重新着色
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else {
                    // 情况2和3：叔节点是黑色
                    if (node == node->parent->left) {
                        // 情况2：节点是父节点的左子节点，先右旋转
                        node = node->parent;
                        rightRotate(node);
                    }
                    // 情况3：节点是父节点的右子节点，重新着色并左旋转
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    leftRotate(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    /**
     * @brief 修复删除后的红黑树性质
     * @param node 被删除节点的替代节点
     */
    void fixRemove(RBTreeNode* node) {
        while (node != root && node->color == BLACK) {
            if (node == node->parent->left) {
                // 节点是父节点的左子节点
                RBTreeNode* sibling = node->parent->right;
                
                if (sibling->color == RED) {
                    // 情况1：兄弟节点是红色
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    leftRotate(node->parent);
                    sibling = node->parent->right;
                }
                
                if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                    // 情况2：兄弟节点的两个子节点都是黑色
                    sibling->color = RED;
                    node = node->parent;
                }
                else {
                    if (sibling->right->color == BLACK) {
                        // 情况3：兄弟节点的右子节点是黑色
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        rightRotate(sibling);
                        sibling = node->parent->right;
                    }
                    // 情况4：兄弟节点的右子节点是红色
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    sibling->right->color = BLACK;
                    leftRotate(node->parent);
                    node = root;
                }
            }
            else {
                // 节点是父节点的右子节点（对称情况）
                RBTreeNode* sibling = node->parent->left;
                
                if (sibling->color == RED) {
                    // 情况1：兄弟节点是红色
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rightRotate(node->parent);
                    sibling = node->parent->left;
                }
                
                if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
                    // 情况2：兄弟节点的两个子节点都是黑色
                    sibling->color = RED;
                    node = node->parent;
                }
                else {
                    if (sibling->left->color == BLACK) {
                        // 情况3：兄弟节点的左子节点是黑色
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        leftRotate(sibling);
                        sibling = node->parent->left;
                    }
                    // 情况4：兄弟节点的左子节点是红色
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    sibling->left->color = BLACK;
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }
        node->color = BLACK;
    }

    /**
     * @brief 中序遍历打印树（递归实现）
     * @param node 当前节点
     */
    void print(RBTreeNode* node) {
        if (node == nil) {
            return;
        }
        print(node->left);
        cout << node->value << "(" << (node->color == RED ? "R" : "B") << ") ";
        print(node->right);
    }

    /**
     * @brief 打印整棵树（中序遍历）
     */
    void print() {
        if (root == nil) {
            cout << "Tree is empty" << endl;
            return;
        }
        print(root);
        cout << endl;
    }
};