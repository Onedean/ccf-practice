/* 
问题描述
　　有 N 个非零且各不相同的整数。请你编一个程序求出它们中有多少对相反数(a 和 -a 为一对相反数)。
输入格式
　　第一行包含一个正整数 N。(1 ≤ N ≤ 500)。
　　第二行为 N 个用单个空格隔开的非零整数,每个数的绝对值不超过1000,保证这些整数各不相同。
输出格式
　　只输出一个整数,即这 N 个数中包含多少对相反数。
样例输入
5
1 2 3 -1 -2
样例输出
2
 */
/*
    unique()是C++标准库函数里面的函数，
    其功能是去除相邻的重复元素（只保留一个），所以使用前需要对数组进行排序
    返回不重复数组长度，实际上是将重复元素隐藏到后面了
*/
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
int main()
{
    int n, a[500];
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        a[i] = abs(a[i]);
    }
    sort(a, a + n);
    cout << n - (unique(a, a + n) - a);
    return 0;
}