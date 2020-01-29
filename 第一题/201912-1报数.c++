/* 
题目：甲乙丙丁玩一个游戏打发时间，游戏规则为四人轮流从1报数，
    遇到7及其倍数或含7的数跳过，报了n个数（不计跳过的数），游戏结束
统计每个人各自跳过几次
输入：正整数n
输出：四个数（分四行），即甲乙丙丁四人各自跳过的次数
 */
#include <iostream>
#include <string>
using namespace std;
int main()
{
    int n, num, a[4] = {0};
    cin >> n;
    while (n)
    {
        num++;
        if (!(num % 7) || to_string(num).find('7') != string::npos)
            a[num % 4]++;
        else
            n--;
    }
    cout << a[1] << endl
         << a[2] << endl
         << a[3] << endl
         << a[0];
    return 0;
}