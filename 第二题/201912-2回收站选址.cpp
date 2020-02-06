/* 
题目描述
开学了，可是校园里堆积了不少垃圾杂物。热心的同学们纷纷自发前来清理，为学校注入正能量~
通过无人机航拍我们已经知晓了n处尚待清理的垃圾位置，其中第i（1<=i<=n）处的坐标为（x，y），
保证所有的坐标均为整数。我们希望在垃圾集中的地方建立些回收站。具体来说，对于一个位置（x, y）
是否适合建立回收站，我们主要考虑以下几点：（x, y）必须是整数坐标，且该处存在垃圾：上下左右
四个邻居位置，即（x, y+1），（x, y-1），（x+1, y）和（x-1, y）处，必须全部存在垃圾：进一步地，
我们会对满足上述两个条件的选址进行评分，分数为不大于4的自然数，表示在（x±1，y±1）四个对角位置
中有几处存在垃圾。现在，请你统计一下每种得分的选址个数。

输入
从标准输入读入数据。输入总共有n+1行。
第1行包含一个正整数n，表示已查明的垃圾点个数。
第1+i行（1<=i<=n）包含由一个空格分隔的两个整数xi和yi，表示第i处垃圾的坐标。
保证输入的n个坐标互不相同。
输出
输出到标准输出。
输出共五行，每行一个整数，依次表示得分为0、1、2、3和4的回收站选址个数。

输入样例1
7
1 2
2 1
0 0
1 1
1 0
2 0
0 1
输出样例1
0
0
1
0
0
样例解释1
   3
   2 *
   * # *
-1 * * * 3 4 5
如图所示，仅有（1，1）可选为回收站地址，评分为2.

输入样例2
2
0 0
-100000 10
输出样例2
0
0
0
0
0
样例解释2
不存在可选地址。

输入样例3
11
9 10
10 10
11 10
12 10
13 10
11 9
11 8
12 9
10 9
10 11
12 11
输出样例3
0
2
1
0
0
样例解释3
1分选址：（10，10）和（12，10）；
2分选址：（11，9）

提示
测试点1和2，保证对于任意的i皆满足0<=xi, yi<=2；
测试点3、4和5，保证对于任意的i皆满足0<=xi, yi<= 500；
测试点6、7和8，保证对于任意的i皆满足0<=xi, yi<= 10^9；
测试点9和10，保证对于任意的i皆满足|xi|, |yi|<=10^9，即坐标可以是负数。
所有的测试点保证1<=n<=10^3。
 */
#include <iostream>
using namespace std;
struct Node
{
    int x, y;
} point[2000];
int main()
{
    int n, hashTable[5] = {0};
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> point[i].x >> point[i].y;
    for (int i = 0; i < n; i++)
    {
        int num = 0;
        for (int j = 0; j < n; j++)
        {
            if (point[i].x - 1 == point[j].x && point[i].y == point[j].y)
                num++;
            if (point[i].x + 1 == point[j].x && point[i].y == point[j].y)
                num++;
            if (point[i].x == point[j].x && point[i].y + 1 == point[j].y)
                num++;
            if (point[i].x == point[j].x && point[i].y - 1 == point[j].y)
                num++;
        }
        if (num == 4)
        {
            int total = 0;
            for (int k = 0; k < n; k++)
            {
                if (point[i].x + 1 == point[k].x && point[i].y + 1 == point[k].y)
                    total++;
                if (point[i].x + 1 == point[k].x && point[i].y - 1 == point[k].y)
                    total++;
                if (point[i].x - 1 == point[k].x && point[i].y + 1 == point[k].y)
                    total++;
                if (point[i].x - 1 == point[k].x && point[i].y - 1 == point[k].y)
                    total++;
            }
            hashTable[total]++;
        }
    }
    for (int i = 0; i < 5; i++)
        cout << hashTable[i] << endl;
    return 0;
}