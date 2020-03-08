/* 
1024块
---
| |   8块->一个条带
|_|
| |   8块->一个条带
|_|
| |
| |
...
| |   8块->一个条带
|_|
注意：
1、本题【题目描述】中说明了该硬盘的块大小为4字节，又2个字符1个字节，也即输入中8个字符为4个字节即1块
2、块所处的磁盘号 = ( 输入块号 / 条带大小s ) % 磁盘数n   (即b/s%n)
3、后台数据有点问题，不用考虑l<=n即可AC
 */
#include <bits/stdc++.h>
using namespace std;
char data[1000][82000];
int main()
{
    int n, s, l, id, m, b;
    cin >> n >> s >> l;
    for (int i = 0; i < l; i++)
    {
        scanf("%d ", &id);             // 空格勿忘读取
        fgets(data[id], 82000, stdin); //82000是最大输入数目，stdin是标准输入，一般指键盘输入到缓冲区里的东西
    }
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> b;
        if (b >= strlen(data[id]) / 8 * (n - 1)) // 块号超过阵列长度
        {
            cout << "-" << endl;
            continue;
        }
        int disk = b / s % n;                                            //先确定位于哪块磁盘，即磁盘号
        int stripe = b / s / n;                                          //然后确定它在磁盘的哪个条带（先不考虑校验块），即条带号
        int check = n - 1 - disk;                                        // 再确定校验盘所处的位置
        int count = stripe < check ? 0 : (stripe - check) / (n - 1) + 1; // 得出前面校验盘的数量
        int dataPos = (stripe + count) * s + (b % s);                    //再确定磁盘中的哪个位置，即数据的位置
        for (int j = dataPos * 8; j < dataPos * 8 + 8; ++j)
            printf("%c", data[disk][j]);
        cout << endl;
    }
    return 0;
}