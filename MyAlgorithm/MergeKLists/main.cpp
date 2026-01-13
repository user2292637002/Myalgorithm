#include<iostream>
#include<climits>
#include<string>
#include<vector>
#include<unordered_map>
#include<map>
#include<set>
#include<stack>
#include<algorithm>
#include<queue>
using namespace std;

// 链表节点结构体
struct ListNode
{
    int val;              // 节点存储的值
    ListNode* next;       // 指向下一个节点的指针
    ListNode() : val(0), next(nullptr) {}                                    // 默认构造函数
    ListNode(int x) : val(x), next(nullptr) {}                              // 带值构造函数
    ListNode(int x, ListNode* nextNode) : val(x), next(nextNode) {}          // 带值和下一个节点的构造函数
};

// 根据数组创建链表
// @param arr: 数组首地址
// @param n: 数组长度
// @return: 返回链表的头节点指针
ListNode* InitList(int* arr, int n)
{
    if (n <= 0) return nullptr;  // 边界检查：数组长度为0或负数，返回空指针

    // 创建头节点，值为数组第一个元素
    ListNode* head = new ListNode(*arr);
    ListNode* current = head;  // current 用于追踪当前链表的最后一个节点

    // 从数组第二个元素开始，依次创建新节点并连接到链表
    for (int i = 1; i < n; i++)
    {
        ListNode* newNode = new ListNode(*(arr + i));  // 创建新节点，值为 arr[i]
        current->next = newNode;  // 将新节点连接到当前链表的末尾
        current = newNode;         // 更新 current 指向新的末尾节点
    }
    return head;  // 返回链表的头节点
}

class Solution
{
public:
    // 自定义比较器结构体，用于优先队列（最小堆）
    // 优先队列默认是最大堆，我们需要最小堆，所以比较器返回 n1->val > n2->val
    // 这样值小的节点会排在队列前面
    struct comp {
        bool operator() (const ListNode* n1, const ListNode* n2) {
            return n1->val > n2->val;  // 返回 true 表示 n1 的优先级低于 n2（值大的优先级低）
        }
    };

    // 合并 K 个有序链表
    // 算法思路：使用优先队列（最小堆）维护所有链表的当前最小节点
    // 每次从堆顶取出最小节点，连接到结果链表，然后将该节点的下一个节点加入堆中
    // 时间复杂度：O(N log K)，其中 N 是所有节点的总数，K 是链表数量
    // 空间复杂度：O(K)，优先队列最多存储 K 个节点
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 注意：priority_queue 第三个比较器参数需要的是类型，不是对象
        // 如果使用 lambda 作为比较器，需要使用 decltype 获取其类型：
        // auto comp = [](const ListNode* n1, const ListNode* n2) {
        //     return n1->val > n2->val;
        // };
        // priority_queue<ListNode*, vector<ListNode*>, decltype(comp)> pq(comp);

        // 创建最小堆（优先队列），存储所有链表的当前头节点
        priority_queue<ListNode*, vector<ListNode*>, comp> pq;

        // 将所有非空链表的头节点加入优先队列
        // 这样队列中始终维护着所有链表当前的最小节点
        for (auto& list : lists) {
            if (list) {  // 只添加非空链表
                pq.push(list);
            }
        }

        // 使用虚拟头节点简化代码，避免处理头节点的特殊情况
        ListNode* dummy = new ListNode();
        ListNode* cur = dummy;  // cur 指向结果链表的当前末尾节点

        // 当优先队列不为空时，持续合并
        while (!pq.empty()) {
            // 取出当前所有链表中的最小节点
            ListNode* tmp = pq.top();
            pq.pop();

            // 将最小节点连接到结果链表
            cur->next = tmp;
            cur = cur->next;  // 更新结果链表的末尾指针

            // 如果该节点还有下一个节点，将下一个节点加入优先队列
            // 这样队列中始终有该链表的当前最小节点
            if (tmp->next) {
                pq.push(tmp->next);
            }
        }

        // 返回合并后的链表头节点（跳过虚拟头节点）
        return dummy->next;
    }

private:
    // 合并两个有序链表（辅助函数，当前代码中未使用，但保留作为参考）
    // 算法思路：使用双指针同时遍历两个链表，比较节点值，将较小的节点连接到结果链表
    // 时间复杂度：O(n + m)，其中 n 和 m 分别是两个链表的长度
    // 空间复杂度：O(1)，只使用了常数额外空间
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        // 边界情况：如果其中一个链表为空，直接返回另一个链表
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;

        // 使用虚拟头节点简化代码，避免处理头节点的特殊情况
        ListNode* head = new ListNode(0);
        ListNode* current = head;  // current 指向结果链表的当前末尾节点

        // 同时遍历两个链表，比较节点值
        while (list1 != nullptr && list2 != nullptr)
        {
            // 将值较小的节点连接到结果链表
            if (list1->val < list2->val)
            {
                current->next = list1;  // 连接 list1 的当前节点
                list1 = list1->next;     // list1 指针后移
            }
            else
            {
                current->next = list2;  // 连接 list2 的当前节点
                list2 = list2->next;     // list2 指针后移
            }
            current = current->next;  // 更新结果链表的末尾指针
        }

        // 将剩余的非空链表连接到结果链表
        // 由于链表已经有序，直接连接剩余部分即可
        if (list1 != nullptr)
        {
            current->next = list1;  // list1 还有剩余节点
        }
        else
        {
            current->next = list2;  // list2 还有剩余节点
        }

        // 返回合并后的链表头节点（跳过虚拟头节点）
        return head->next;
    }
};





int main()
{
    // 创建 5 个测试数组，每个数组包含 5 个有序元素
    int a[] = { 1,2,3,4,5 };
    int b[] = { 6,7,8,9,10 };
    int c[] = { 11,12,13,14,15 };
    int d[] = { 16,17,18,19,20 };
    int e[] = { 21,22,23,24,25 };

    // 根据数组创建 5 个有序链表
    ListNode* list1 = InitList(a, 5);  // 链表1: 1->2->3->4->5
    ListNode* list2 = InitList(b, 5);  // 链表2: 6->7->8->9->10
    ListNode* list3 = InitList(c, 5);  // 链表3: 11->12->13->14->15
    ListNode* list4 = InitList(d, 5);  // 链表4: 16->17->18->19->20
    ListNode* list5 = InitList(e, 5);  // 链表5: 21->22->23->24->25

    // 将所有链表的头节点放入向量中
    vector<ListNode*> lists = { list1, list2, list3, list4, list5 };

    // 调用 mergeKLists 合并所有链表
    // 预期结果：1->2->3->4->5->6->7->8->9->10->11->12->13->14->15->16->17->18->19->20->21->22->23->24->25
    ListNode* merged = Solution().mergeKLists(lists);

    // 遍历并打印合并后的链表
    while (merged != nullptr)
    {
        cout << merged->val << " ";
        merged = merged->next;
    }
    cout << endl;

    return 0;
}





