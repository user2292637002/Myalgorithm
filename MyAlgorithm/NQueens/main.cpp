#include<iostream>
#include<vector>
#include<functional>
using namespace std;

class Solution
{
public:
    /// @brief 解决 N 皇后问题
    /// @param n 棋盘大小（n x n）和皇后数量
    /// @return 所有可能的解，每个解是一个字符串数组，表示一种放置方式
    /// 
    /// N 皇后问题：在 n×n 的棋盘上放置 n 个皇后，使得它们不能相互攻击
    /// 皇后可以攻击同一行、同一列、同一对角线上的棋子
    /// 
    /// 算法思路：回溯算法
    /// 1. 逐行放置皇后（每行只能放一个）
    /// 2. 使用数组记录列和对角线的占用情况，快速判断是否可以放置
    /// 3. 如果当前行所有位置都不能放置，回溯到上一行
    /// 4. 如果成功放置了 n 个皇后，保存当前解
    ///
    /// 时间复杂度：O(n!)，最坏情况下需要尝试所有排列
    /// 空间复杂度：O(n)，用于存储棋盘和标记数组
    vector<vector<string>> solveNQueens(int n)
    {
        // 存储所有解
        vector<vector<string>> result;

        // 初始化棋盘：n x n 的棋盘，所有位置初始化为 '.'
        // board[i][j] 表示第 i 行第 j 列，'Q' 表示放置皇后，'.' 表示空位
        vector<string> board(n, string(n, '.'));

        // cols[i] 表示第 i 列是否已被占用
        // 如果 cols[i] == true，说明第 i 列已经有皇后了
        vector<bool> cols(n, false);

        // diag1[i] 表示主对角线（从左上到右下）是否已被占用
        // 主对角线索引计算：row + col
        // 同一主对角线上，row + col 的值相同
        // 例如：对于 4x4 棋盘，主对角线索引范围是 0 到 6
        //   (0,0)=0, (0,1)=1, (0,2)=2, (0,3)=3
        //   (1,0)=1, (1,1)=2, (1,2)=3, (1,3)=4
        //   (2,0)=2, (2,1)=3, (2,2)=4, (2,3)=5
        //   (3,0)=3, (3,1)=4, (3,2)=5, (3,3)=6
        // 共有 2*n - 1 条主对角线
        vector<bool> diag1(2 * n - 1, false);

        // diag2[i] 表示副对角线（从右上到左下）是否已被占用
        // 副对角线索引计算：row - col + n - 1
        // 同一副对角线上，row - col 的值相同
        // 加上 n - 1 是为了将索引转换为非负数（因为 row - col 可能为负）
        // 例如：对于 4x4 棋盘，副对角线索引范围是 0 到 6
        //   (0,0)=3, (0,1)=2, (0,2)=1, (0,3)=0
        //   (1,0)=4, (1,1)=3, (1,2)=2, (1,3)=1
        //   (2,0)=5, (2,1)=4, (2,2)=3, (2,3)=2
        //   (3,0)=6, (3,1)=5, (3,2)=4, (3,3)=3
        // 共有 2*n - 1 条副对角线
        vector<bool> diag2(2 * n - 1, false);

        // 回溯函数：使用 lambda 表达式定义，[&] 表示按引用捕获外部变量
        // row 表示当前要放置皇后的行号（从 0 开始）
        function<void(int)> backtrack = [&](int row)
            {
                // 递归终止条件：如果已经放置了 n 个皇后（row == n），说明找到了一个解
                if (row == n)
                {
                    // 将当前棋盘状态保存到结果中
                    result.push_back(board);
                    return;
                }

                // 尝试在当前行的每一列放置皇后
                for (int col = 0; col < n; ++col)
                {
                    // 检查当前位置是否可以放置皇后
                    // 需要同时满足三个条件：
                    // 1. 该列没有被占用（cols[col] == false）
                    // 2. 该主对角线没有被占用（diag1[row + col] == false）
                    // 3. 该副对角线没有被占用（diag2[row - col + n - 1] == false）
                    if (cols[col] || diag1[row + col] || diag2[row - col + n - 1])
                    {
                        // 如果当前位置不能放置，尝试下一列
                        continue;
                    }

                    // 在当前位置放置皇后
                    board[row][col] = 'Q';

                    // 标记该列、主对角线、副对角线已被占用
                    // 注意：这里使用链式赋值，同时设置三个标记为 true
                    cols[col] = diag1[row + col] = diag2[row - col + n - 1] = true;

                    // 递归：尝试在下一行放置皇后
                    backtrack(row + 1);

                    // 回溯：撤销当前选择，恢复状态
                    // 将棋盘位置恢复为 '.'
                    board[row][col] = '.';
                    // 取消标记：将该列、主对角线、副对角线的占用标记清除
                    cols[col] = diag1[row + col] = diag2[row - col + n - 1] = false;
                }
                // 如果当前行的所有列都不能放置，函数返回，自动回溯到上一行
            };

        // 从第 0 行开始回溯
        backtrack(0);

        return result;
    }

    int totalNQueens(int n)
    {
		return solveNQueens(n).size();
	}
};





int main()
{
    Solution sol;
    for(int n = 1; n <= 9; ++n)
    {
        int count = sol.totalNQueens(n);
        cout << "Number of solutions for " << n << "-Queens: " << count << endl;
	}


    return 0;
}





