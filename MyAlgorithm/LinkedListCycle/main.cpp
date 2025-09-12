/*
题目描述：
给你一个链表的头节点 head ，判断链表中是否有环。
如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，
评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。注意：pos 不作为参数进行传递。
仅仅是为了标识链表的实际情况。
如果链表中存在环，则返回 true 。 否则，返回 false 。

示例：
输入：head = [3,2,0,-4], pos = 1
输出：true
解释：链表中有一个环，其尾部连接到第二个节点。

输入：head = [1,2], pos = 0
输出：true
解释：链表中有一个环，其尾部连接到第一个节点。

输入：head = [1], pos = -1
输出：false
解释：链表中没有环。

提示：
使用“快慢指针”（Floyd 判圈算法）。定义两个指针，一个慢指针 slow 每次移动一步，一个快指针 fast 每次移动两步。
如果链表中存在环，那么快指针最终会追上慢指针（两者相遇）。如果快指针到达了链表末尾（null），则说明没有环。
*/

#include"LinkedList.h"
#include<vector>
int main()
{
    int n;
    cout << "请输入数组大小: ";
    cin >> n;
    int* arr = new int[n];
    cout << "请输入 " << n << " 个数字: ";
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        arr[i] = x;
    }

    LinkNode* head = InitLinkedList(arr, n);

    PrintList(head);

    DeleteList(head);

    delete[]arr;
}