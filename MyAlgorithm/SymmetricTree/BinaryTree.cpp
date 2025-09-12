#include"BinaryTree.h"

/**
 * @brief ���ݲ����ַ�������������
 *
 * Լ����
 * 1. �����ַ��������򣨹�����ȣ�˳������ڵ�ֵ��
 * 2. �� INT_MIN��ͨ��ȡ -2147483648����ʾ��ָ�룻
 * 3. ���� INT_MIN ������������Ϊ�䴴�� TreeNode��
 * 4. ���ع����õĸ�ָ�룬�����ַ����� INT_MIN �򷵻� nullptr��
 *
 * @param line �ո�ָ��Ĳ������У����� "1 2 3 -2147483648 -2147483648 4 5"
 * @return TreeNode* ������ĸ��ڵ�ָ��
 */
TreeNode* CreateBinaryTree_LevelOrder(const std::string& line) {
    /* ---- 1. ������һ��ֵ���������ڻ�Ϊ������־��ֱ�ӷ��� ---- */
    stringstream ss(line); // ���ַ�������������
    int val;
    if (!(ss >> val) || val == INT_MIN) return nullptr;

    /* ---- 2. �������ڵ㲢������У�׼��������ȹ��� ---- */
    TreeNode* root = new TreeNode(val); // ���ڵ�
    queue<TreeNode*> q;            // �������У���Ŵ�����ڵ�
    q.push(root);                       // ��ʼֻ�и��ڵ�

    /* ---- 3. ������ѭ����ÿ��ȡ�����׽ڵ㣬���Ը�������Һ��� ---- */
    while (!q.empty()) {
        TreeNode* cur = q.front(); // ��ǰҪ���Һ��ӡ��Ľڵ�
        q.pop();

        /* ---- 3.1 �������� ---- */
        if (ss >> val && val != INT_MIN) {           // ������Чֵ
            cur->leftChild = new TreeNode(val);      // �½�����
            q.push(cur->leftChild);                  // ������ӣ���������������
        }
        // ������ INT_MIN ��û�и���ֵ��cur->leftChild ���� nullptr

        /* ---- 3.2 �����Һ��ӣ��߼�ͬ���ӣ� ---- */
        if (ss >> val && val != INT_MIN) {
            cur->rightChild = new TreeNode(val);
            q.push(cur->rightChild);
        }
    } // end while

    /* ---- 4. ���ع����õĸ�ָ�� ---- */
    return root;
}


/**
 * @brief ��ǰ������ [pl..pr] ���������� [il..ir] ��������
 *
 * ǰ�᣺pre �� in �����ظ�Ԫ��
 *
 * @param pre     ǰ���������
 * @param pl      ��ǰ������ǰ���е�����±�
 * @param pr      ��ǰ������ǰ���е��Ҷ��±�
 * @param in      �����������
 * @param il      ��ǰ�����������е�����±�
 * @param ir      ��ǰ�����������е��Ҷ��±�
 * @param inMap   ����ֵ���±�Ĺ�ϣ������ O(1) �ҵ���λ��
 * @return TreeNode* ��ǰ�����ĸ��ڵ�ָ��
 */
TreeNode* buildPI(const int pre[], int pl, int pr,
    const int in[], int il, int ir,
    unordered_map<int, int>& inMap)
{
    /* 1. ����Ϊ�գ����ؿ����� */
    if (pl > pr) return nullptr;

    /* 2. ǰ���һ��Ԫ�ؾ��ǵ�ǰ�����ĸ� */
    int rootVal = pre[pl];
    TreeNode* node = new TreeNode(rootVal);

    /* 3. ���������ҵ�����λ�� k���������г������������� */
    int k = inMap[rootVal];      // ���������е��±�
    int leftSize = k - il;       // �������ڵ����

    /* 4. �ݹ鹹��������
       ǰ����������ȡ leftSize ��Ԫ��  [pl+1 .. pl+leftSize]
       ��������                         [il .. k-1]        */
    node->leftChild = buildPI(pre, pl + 1, pl + leftSize,
        in, il, k - 1, inMap);

    /* 5. �ݹ鹹��������
       ǰ��ʣ�µ�Ԫ��                     [pl+leftSize+1 .. pr]
       �����Ұ��                         [k+1 .. ir]        */
    node->rightChild = buildPI(pre, pl + leftSize + 1, pr,
        in, k + 1, ir, inMap);

    /* 6. ���ص�ǰ�����ĸ�������һ���ָ�� */
    return node;
}

/**
 * @brief �û��Ѻýӿڣ���ǰ������򹹽����ö�����
 *
 * @param pre ǰ��������飬���� n
 * @param in  ����������飬���� n
 * @param n   ���鳤�ȣ��ڵ������
 * @return TreeNode* ����ָ�룬�������� nullptr
 */
TreeNode* CreateBinaryTree_PreIn(const int pre[], const int in[], int n)
{
    /* 0. ���п��� */
    if (n == 0) return nullptr;

    /* 1. �Ȱ�����ֵ���±�����ϣ������ÿ�β��� O(1) */
    unordered_map<int, int> inMap;
    for (int i = 0; i < n; ++i) inMap[in[i]] = i;

    /* 2. ���õݹ鸨������ʼ����Ϊ�������ķ�Χ */
    return buildPI(pre, 0, n - 1, in, 0, n - 1, inMap);
}


TreeNode* CreateBinaryTree_PostIn(const int post[], const int in[], int n)
{

}
