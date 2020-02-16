/* 
问题描述
　　有一类节日的日期并不是固定的，而是以“a月的第b个星期c”的形式定下来的，比如说母亲节就定为
    每年的五月的第二个星期日。
　　现在，给你a，b，c和y1, y2(1850 ≤ y1, y2 ≤ 2050)，希望你输出从公元y1年到公元y2年间的
    每年的a月的第b个星期c的日期。
　　提示：关于闰年的规则：年份是400的整数倍时是闰年，否则年份是4的倍数并且不是100的倍数时是
    闰年，其他年份都不是闰年。例如1900年就不是闰年，而2000年是闰年。
　　为了方便你推算，已知1850年1月1日是星期二。
输入格式
　　输入包含恰好一行，有五个整数a, b, c, y1, y2。其中c=1, 2, ……, 6, 7分别表示星期一、二、……、六、日。
输出格式
　　对于y1和y2之间的每一个年份，包括y1和y2，按照年份从小到大的顺序输出一行。
　　如果该年的a月第b个星期c确实存在，则以"yyyy/mm/dd"的格式输出，即输出四位数的年份，两位数的月份，
    两位数的日期，中间用斜杠“/”分隔，位数不足时前补零。
　　如果该年的a月第b个星期c并不存在，则输出"none"（不包含双引号)。
样例输入
5 2 7 2014 2015
样例输出
2014/05/11
2015/05/10
评测用例规模与约定
　　所有评测用例都满足：1 ≤ a ≤ 12，1 ≤ b ≤ 5，1 ≤ c ≤ 7，1850 ≤ y1, y2 ≤ 2050。
 */
#include <iostream>
using namespace std;
int leap(int year)
{
    return year % 400 || (!(year % 4) && year % 100);
}
int main()
{
    int a, b, c, y1, y2, sum = 0, week, tempDay, mon[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    cin >> a >> b >> c >> y1 >> y2;
    for (int i = 1850; i < y1; i++)
        sum += 365 + leap(i);
    for (int i = y1; i <= y2; i++)
    {
        mon[1] = leap(i) ? 29 : 28;
        for (int j = 0; i < a - 1; j++)
            sum += mon[j];
        /* week = (sum + 2) % 7 ? (sum + 2) % 7 : 7; //计算当年当月第一天是星期几
        cout << week << endl;
        tempDay = (b - 1) * 7;
        if (week <= c)
            tempDay += c - week + 1;
        else
            tempDay += 7 - (week - c) + 1;
        if (tempDay <= mon[a])
            printf("%d/%02d/%02d\n", i, a, tempDay);
        else
            cout << "none" << endl; */
        for (int j = a; i < 12; j++)
            sum += mon[j];
    }
    return 0;
}