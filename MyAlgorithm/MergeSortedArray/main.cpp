/*
��Ŀ������
���������� �ǵݼ�˳�� ���е��������� nums1 �� nums2�������������� m �� n ���ֱ��ʾ nums1 �� nums2 �е�Ԫ����Ŀ��
���� �ϲ� nums2 �� nums1 �� ��ʹ�ϲ��������ͬ���� �ǵݼ�˳�� ���С�
ע�⣺���ս��Ӧ�ô洢�� nums1 �У�Ϊ��Ӧ�����������nums1 �ĳ�ʼ����Ϊ m + n������ǰ m ��Ԫ�ر�ʾӦ�ϲ���Ԫ�أ�
�� n ��Ԫ��Ϊ 0 ��Ӧ���ԡ�nums2 �ĳ���Ϊ n��

ʾ����
���룺nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
�����[1,2,2,3,5,6]
���ͣ���Ҫ�ϲ� [1,2,3] �� [2,5,6] ��
�ϲ������ [1,2,2,3,5,6] ������б��Ӵֱ�ע��Ϊ nums1 �е�Ԫ�ء�

���룺nums1 = [1], m = 1, nums2 = [], n = 0
�����[1]
���ͣ���Ҫ�ϲ� [1] �� [] ��
�ϲ������ [1] ��

���룺nums1 = [0], m = 0, nums2 = [1], n = 1
�����[1]
���ͣ���Ҫ�ϲ� [] �� [1] ��
�ϲ������ [1] ��
ע�⣬��Ϊ m = 0 ������ nums1 ��û��Ԫ�ء�nums1 �н���� 0 ������Ϊ��ȷ���ϲ��������˳����ŵ� nums1 �С�

��ʾ��

��ֱ�ӵķ����Ǵ�ǰ����ϲ���������Ҫ����Ŀռ����ݴ� nums1 ��Ԫ�ء�
���ŵķ����ǴӺ���ǰ�ϲ���ʹ������ָ�룺
i ָ�� nums1 ����ЧԪ�ص�ĩβ (m-1)��
j ָ�� nums2 ��ĩβ (n-1)��
k ָ�� nums1 ������ĩβ (m+n-1)��
�Ƚ� nums1[i] �� nums2[j]�����ϴ���Ǹ��ŵ� nums1[k]��Ȼ����Ӧָ��ǰ�ơ��������Ա��⸲�� nums1 ����δ�����Ԫ�ء�
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
    cout << "���� nums1 ��Ч���� m��";
    cin >> m;
    cout << "���� nums2 ���� n��";
    cin >> n;

    const int total = m + n;
    int* nums1 = new int[total];   
    int* nums2 = new int[n];

    cout << "���� nums1 �� " << m << " ���ǵݼ�Ԫ�أ�";
    for (int i = 0; i < m; ++i) cin >> nums1[i];
    for (int i = m; i < total; ++i) nums1[i] = 0;  

    cout << "���� nums2 �� " << n << " ���ǵݼ�Ԫ�أ�";
    for (int i = 0; i < n; ++i) cin >> nums2[i];

    merge(nums1, m, nums2, n);

    cout << "�ϲ������";
    for (int i = 0; i < total; ++i) cout << nums1[i] << ' ';
    cout << '\n';

    delete[] nums1;
    delete[] nums2;
    return 0;
}