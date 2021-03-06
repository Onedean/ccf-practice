/* 
问题描述
　　我们把一个数称为有趣的，当且仅当：
　　1. 它的数字只包含0, 1, 2, 3，且这四个数字都出现过至少一次。
　　2. 所有的0都出现在所有的1之前，而所有的2都出现在所有的3之前。
　　3. 最高位数字不为0。
　　因此，符合我们定义的最小的有趣的数是2013。除此以外，4位的有趣的数还有两个：2031和2301。
　　请计算恰好有n位的有趣的数的个数。由于答案可能非常大，只需要输出答案除以1000000007的余数。
输入格式
　　输入只有一行，包括恰好一个正整数n (4 ≤ n ≤ 1000)。
输出格式
　　输出只有一行，包括恰好n 位的整数中有趣的数的个数除以1000000007的余数。
样例输入
4
样例输出
3
 */
/* 
用动态规划来解决。共有如下六种状态：
0、  2                  状态0补2
1、  2 0                状态0补0，状态1补2或0
2、  2 3                状态0补3，状态2补3
3、  2 0 1              状态1补1、状态3补1或3
4、  含2 0 3            状态1补3、状态2补0、状态4补0或3
5、  2,0,1,3任意4个数    状态3补3、状态4补1、状态5补1或3
 */
#include <iostream>
#define MOD 1000000007
using namespace std;
long long f[1000][6];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int j = i - 1;
        f[i][0] = 1;
        f[i][1] = (f[j][0] + f[j][1] * 2) % MOD;
        f[i][2] = (f[j][0] + f[j][2]) % MOD;
        f[i][3] = (f[j][1] + f[j][3] * 2) % MOD;
        f[i][4] = (f[j][1] + f[j][2] + f[j][4] * 2) % MOD;
        f[i][5] = (f[j][3] + f[j][4] + f[j][5] * 2) % MOD;
    }
    cout << f[n][5];
    return 0;
}