/* 
【题目背景】
    二十四点是一款著名的纸牌游戏，其游戏的目标是使用 3 个加减乘除运算使得 4张纸牌上数字的运算结果为 24。
【题目描述】
    定义每一个游戏由 4 个从 1-9 的数字和 3个四则运算符组成，保证四则运算符将数字两两隔开，不存在括号
    和其他字符，运算顺序按照四则运算顺序进行。其中加法用符号 + 表示，减法用符号 -表示，乘法用小写字母
     x 表示，除法用符号 / 表示。在游戏里除法为整除，例如 2 / 3 = 0，3 / 2 = 1, 4 / 2 = 2。
    老师给了你 n 个游戏的解，请你编写程序验证每个游戏的结果是否为 24 。
【输入格式】
    从标准输入读入数据。第一行输入一个整数 n，从第 2 行开始到第 n + 1 行中，每一行包含一个长度为 7的字
    符串，为上述的 24 点游戏，保证数据格式合法。
【输出格式】
    输出到标准输出。 包含 n 行，对于每一个游戏，如果其结果为 24 则输出字符串 Yes，否则输出字符串 No。
【样例1输入】
10
9+3+4x3
5+4x5x5
7-9-9+8
5x6/5x4
3+5+7+9
1x1+9-9
1x9-5/9
8/5+6x9
6x7-3x6
6x4+4/5
【样例1输出】
    Yes
    No
    No
    Yes
    Yes
    No
    No
    No
    Yes
    Yes
样例1解释
    9 + 3 + 4 × 3 = 24
    5 + 4 × 5 × 5 = 105
    7 - 9 - 9 + 8 = -3
    5 × 6 / 5 × 4 = 24
    3 + 5 + 7 + 9 = 24
    1 × 1 + 9 - 9 = 1
    1 × 9 - 5 / 9 = 9
    8 / 5 + 6 × 9 = 55
    6 × 7 - 3 × 6 = 24
    6 × 4 + 4 / 5 = 24
 */
#include <iostream>
#include <string>
#include <stack>
using namespace std;
int main()
{
    int n;
    stack<int> num;
    stack<char> op;
    string str;
    cin >> n;
    while (n--)
    {
        cin >> str;
        while (!num.empty()) // 清空上一轮栈
            num.pop();
        while (!op.empty())
            op.pop();
        int i = 0;
        while (i < str.length())
        {
            if (str[i] >= '1' && str[i] <= '9')
                num.push(str[i] - '0');
            else
            {
                if (str[i] == '+')
                    op.push('+');
                else if (str[i] == '-')
                {
                    op.push('+');
                    num.push('0' - str[i + 1]);
                    i++;
                }
                else if (str[i] == '*')
                {
                    int pre = num.top();
                    num.pop();
                    num.push(pre * (str[i + 1] - '0'));
                    i++;
                }
                else if (str[i] == '/')
                {
                    int pre = num.top();
                    num.pop();
                    num.push(pre / (str[i + 1] - '0'));
                    i++;
                }
            }
            i++;
        }
        while (!op.empty())
        {
            int a = num.top();
            num.pop();
            int b = num.top();
            num.pop();
            op.pop();
            num.push(a + b);
        }
        cout << num.top() << endl;
        if (num.top() == 24)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}