/*��Ŀһ������֮��
��Ŀ������
����һ���������� nums ��һ������Ŀ��ֵ target�������ڸ��������ҳ� ��ΪĿ��ֵ target ���� ���� ���������������ǵ������±ꡣ
����Լ���ÿ������ֻ���Ӧһ���𰸡����ǣ�������ͬһ��Ԫ���ڴ��ﲻ���ظ����֡�
����԰�����˳�򷵻ش𰸡�

ʾ����
���룺nums = [2,7,11,15], target = 9
�����[0,1]
���ͣ���Ϊ nums[0] + nums[1] == 9 ������ [0, 1] ��

���룺nums = [3,2,4], target = 6
�����[1,2]

���룺nums = [3,3], target = 6
�����[0,1]


��ʾ��
����ʹ�ù�ϣ�����Ż�����Ч�ʡ����������е�ÿ��Ԫ�� nums[i]��������֪���Ƿ����һ��Ԫ�� nums[j]��ʹ�� nums[i] + nums[j] = target��
��ȼ��� nums[j] = target - nums[i]�����ǿ����ù�ϣ��洢�Ѿ���������Ԫ�ؼ���������
*/

#include <iostream>
#include <vector>
#include <unordered_map> 
using namespace std;

vector<int> twoSum(const vector<int>& nums, int target);

int main() {    
    vector<int> nums;
    int n, target;
    cout << "�����������С: ";
    cin >> n;
    cout << "������ " << n << " ������: ";
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }
    cout << "������Ŀ��ֵ: ";
    cin >> target;
    
    vector<int> result = twoSum(nums, target);

    cout << "���: [";
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}


vector<int> twoSum(const vector<int>& nums, int target) {
    unordered_map<int, int> numToIndex;
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];   
        if (numToIndex.find(complement) != numToIndex.end()) {
            return { numToIndex[complement], i };
        }
        numToIndex[nums[i]] = i;
    }
    return {};
}