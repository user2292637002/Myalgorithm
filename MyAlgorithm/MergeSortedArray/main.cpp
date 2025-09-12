/*
题目描述：
给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。
请你 合并 nums2 到 nums1 中 ，使合并后的数组同样按 非递减顺序 排列。
注意：最终结果应该存储在 nums1 中，为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，
后 n 个元素为 0 ，应忽略。nums2 的长度为 n。

示例：
输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
输出：[1,2,2,3,5,6]
解释：需要合并 [1,2,3] 和 [2,5,6] 。
合并结果是 [1,2,2,3,5,6] ，其中斜体加粗标注的为 nums1 中的元素。

输入：nums1 = [1], m = 1, nums2 = [], n = 0
输出：[1]
解释：需要合并 [1] 和 [] 。
合并结果是 [1] 。

输入：nums1 = [0], m = 0, nums2 = [1], n = 1
输出：[1]
解释：需要合并 [] 和 [1] 。
合并结果是 [1] 。
注意，因为 m = 0 ，所以 nums1 中没有元素。nums1 中仅存的 0 仅仅是为了确保合并结果可以顺利存放到 nums1 中。

提示：

最直接的方法是从前往后合并，但这需要额外的空间来暂存 nums1 的元素。
更优的方法是从后往前合并。使用三个指针：
i 指向 nums1 中有效元素的末尾 (m-1)。
j 指向 nums2 的末尾 (n-1)。
k 指向 nums1 的真正末尾 (m+n-1)。
比较 nums1[i] 和 nums2[j]，将较大的那个放到 nums1[k]，然后相应指针前移。这样可以避免覆盖 nums1 中尚未处理的元素。
*/

#include <iostream>
using namespace std;

void merge(int arr1[], int m, int arr2[], int n) {
    int i = m - 1;
    int j = n - 1;
    int k = m + n - 1;

    while (i >= 0 && j >= 0) {
        if (arr1[i] > arr2[j]) arr1[k--] = arr1[i--];
        else                   arr1[k--] = arr2[j--];
    }
    while (j >= 0) arr1[k--] = arr2[j--];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cout << "输入 nums1 有效长度 m：";
    cin >> m;
    cout << "输入 nums2 长度 n：";
    cin >> n;

    const int total = m + n;
    int* nums1 = new int[total];   
    int* nums2 = new int[n];

    cout << "输入 nums1 的 " << m << " 个非递减元素：";
    for (int i = 0; i < m; ++i) cin >> nums1[i];
    for (int i = m; i < total; ++i) nums1[i] = 0;  

    cout << "输入 nums2 的 " << n << " 个非递减元素：";
    for (int i = 0; i < n; ++i) cin >> nums2[i];

    merge(nums1, m, nums2, n);

    cout << "合并结果：";
    for (int i = 0; i < total; ++i) cout << nums1[i] << ' ';
    cout << '\n';

    delete[] nums1;
    delete[] nums2;
    return 0;
}