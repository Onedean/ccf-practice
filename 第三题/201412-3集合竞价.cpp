/* 
问题描述
　　某股票交易所请你编写一个程序，根据开盘前客户提交的订单来确定某特定股票的开盘价和开盘成交量。
　　该程序的输入由很多行构成，每一行为一条记录，记录可能有以下几种：
　　1. buy p s 表示一个购买股票的买单，每手出价为p，购买股数为s。
　　2. sell p s 表示一个出售股票的卖单，每手出价为p，出售股数为s。
　　3. cancel i表示撤销第i行的记录。
　　如果开盘价为p0，则系统可以将所有出价至少为p0的买单和所有出价至多为p0的卖单进行匹配。因此，此时的
    开盘成交量为出价至少为p0的买单的总股数和所有出价至多为p0的卖单的总股数之间的较小值。
　　你的程序需要确定一个开盘价，使得开盘成交量尽可能地大。如果有多个符合条件的开盘价，你的程序应当输出
    最高的那一个。
输入格式
　　输入数据有任意多行，每一行是一条记录。保证输入合法。股数为不超过10^8的正整数，出价为精确到恰好小数点
    后两位的正实数，且不超过10000.00。
输出格式
　　你需要输出一行，包含两个数，以一个空格分隔。第一个数是开盘价，第二个是此开盘价下的成交量。开盘价需要
    精确到小数点后恰好两位。
样例输入
buy 9.25 100
buy 8.88 175
sell 9.00 1000
buy 9.00 400
sell 8.92 400
cancel 1
buy 100.00 50
样例输出
9.00 450
评测用例规模与约定
　　对于100%的数据，输入的行数不超过5000。
 */


/* 
   buy       价格轴  sell
 100.00(50)
 9.25(取消)
 9.00(400)
             此区间都可以（取buy上找）            
                     9.00(1000)
                     8.92(400)
 8.92(400)
 故：定价9.00，成交量:(400+50)<1000

从buy买价中开始找开盘价！！！每一个开盘价，从开盘价往上求出总买单数，往下找出总卖单数，
找买卖单最小值，更新最大卖单数。
注意
为什么要从买单开始找开盘价，而不是暴力的每个价格试？
可以证明开盘价永远在买单中。简单的举个栗子，假定客人买东西有10元，东西成本卖5元，给你定价，
你会定多少才挣钱？废话肯定10元啊。所以定价是看客人有多少钱，一样的道理，开盘价永远看买单的
价格。用图说话，看下图，稍微改了下数据。在价格轴上，定价杆（开盘价）在某个价格区间之内都可以
达到最大交易量，当然就把杆往上抬，碰到买价为止，所以一定从买价中找开盘价。

坑：
1、cancel i表示撤销第i行的记录（cancel要存储否则后面行数会不对）
“撤销第i行的记录”： 这里的撤销只是撤销记录本身，被撤销记录所造成的影响不会消失！！！比如：
buy 9.00 100
sell 8.88 200
cancel 2
cancel 3
有效的记录是（测试数据得出）：
buy 9.00 100
正确的做法是，如果后面cancel作用在前面cancel上，则不用管。
如果后面的cancel作用在前面已经被cancel作用过的sell和buy上，则每次取反(即，两次cancel相抵消)
2、注意数据10^8要用long long型
 */


#include <iostream>
#include <set>
using namespace std;
struct stock
{
    string op;
    float price;
    long long num;
    int isCannel = 1;
} order[5005];
int main()
{
    int n = 0, index;
    float maxPrice = 0; // 成交价格
    set<float> price;
    long long buyNum, sellNum, dellNum, maxNum = 0;
    while (cin >> order[n++].op)
    {
        if (order[n - 1].op == "cancel")
        {
            cin >> index;
            order[index - 1].isCannel = 0;
            continue;
        }
        cin >> order[n - 1].price >> order[n - 1].num;
    }
    for (int i = 0; i < n; i++) // 用到set<double>容器，它的insert方法会自动根据值得从小到大排列
        if (order[i].op == "buy" && order[i].isCannel)
            price.insert(order[i].price);
    for (set<float>::iterator it = price.begin(); it != price.end(); it++)
    {
        buyNum = 0, sellNum = 0;
        for (int i = 0; i < n; i++)
        {
            if (order[i].isCannel && order[i].op == "buy" && order[i].price >= *it)
                buyNum += order[i].num;
            if (order[i].isCannel && order[i].op == "sell" && order[i].price <= *it)
                sellNum += order[i].num;
        }
        dellNum = min(buyNum, sellNum);
        if (dellNum >= maxNum)
        {
            maxNum = dellNum;
            maxPrice = max(maxPrice, *it);
        }
    }
    printf("%.2f %lld", maxPrice, maxNum);
    return 0;
}