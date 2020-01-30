/* 
题目：第一行为n代表第2行输入n个数，第二行n个顺序或逆序的数（可能相同）
    输出最大、中位（中间的那个数）、最小数(这三个数从大到小输出)
    中位数定义：有序排列后, 当n为奇数时, m=a[(n+1)/2]; 当n为偶数时, m=(a[n/2]+a[n/2+1])/2
样例输入：
4
-2 -1 3 4
样例输出：
4 1 -2
 */
#include <iostream>
using namespace std;
int main()
{
    int n, a[100005];
    float mid;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    if (a[1] < a[n])
        a[n] ^= a[1] ^= a[n] ^= a[1]; // 交换最小最大数
    if (n % 2)
        mid = a[(n + 1) / 2];
    else
        mid = (a[n / 2] + a[n / 2 + 1]) / 2.0;
    if (mid - (int)mid)
        printf("%d %.1f %d", a[1], mid, a[n]);
    else
        printf("%d %.0f %d", a[1], mid, a[n]);
    return 0;
}