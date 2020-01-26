/* 
题目：小明在n棵苹果树上每轮疏果m次
    第1-n行依次为 第n个苹果树上的树木,m个梳果数目
    统计最后果园剩余果树上果实数目，哪棵梳果数目最多，是多少（若出现并列，按次序小的输出）
样例输入：
2 2
10 -3 -1
15 -4 0
样例输出：
17 1 -4
 */
#include <iostream>
using namespace std;
int main()
{
    int n, m, num, dis, disTotal, min = 0, minIndex, sum = 0;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        disTotal = 0;
        cin >> num;
        for (int j = 0; j < m; j++)
        {
            cin >> dis;
            disTotal += dis;
        }
        if (disTotal < min)
        {
            min = disTotal;
            minIndex = i + 1;
        }
        sum += num + disTotal;
    }
    cout << sum << ' ' << minIndex << ' ' << -min;
    return 0;
}