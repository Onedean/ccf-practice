/* 
问题描述
　　给定n个整数，请统计出每个整数出现的次数，按出现次数从多到少的顺序输出。
输入格式
　　输入的第一行包含一个整数n，表示给定数字的个数。
　　第二行包含n个整数，相邻的整数之间用一个空格分隔，表示所给定的整数。
输出格式
　　输出多行，每行包含两个整数，分别表示一个给定的整数和它出现的次数。按出现次数递减的顺序输出。
    如果两个整数出现的次数一样多，则先输出值较小的，然后输出值较大的。
样例输入
12
5 2 3 3 1 3 4 2 5 2 3 5
样例输出
3 4
2 3
5 3
1 1
4 1
评测用例规模与约定
　　1 ≤ n ≤ 1000，给出的数都是不超过1000的非负整数。
 */
#include <iostream>
#include <algorithm>
const int N = 1005;
using namespace std;
struct node
{
    int num, total = 0;
} number[N];
bool cmp(node a, node b)
{
    if (a.total != b.total)
        return a.total > b.total;
    else
        return a.num < b.num;
}
int main()
{
    int n, x;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        number[x].num = x;
        number[x].total++;
    }
    sort(number, number + N, cmp);
    for (int i = 0; number[i].total != 0; i++)
        cout << number[i].num << ' ' << number[i].total << endl;
    return 0;
}