#include <iostream>
#include <algorithm>
#include <list>
#include <sstream>
using namespace std;
struct IP
{
    string ip;
    int len;
    IP(string ip, int len) : ip(ip), len(len) {}
    bool operator<(const IP &a) const
    {
        return ip == a.ip ? len < a.len : ip < a.ip;
    }
};
string toTwo(int n) //转成对应八位二进制
{
    string res = "00000000";
    int k = 7;
    while (n)
    {
        res[k--] = n % 2 + '0'; // 注意+'0'转化为字符
        n /= 2;
    }
    return res;
}
int main()
{
    int n, len, num, i;
    list<IP> lt;
    cin >> n;
    for (int i = 0; i < n; i++) // 第一步读取分离并排序
    {
        string str, singleStr, newStr = "";
        cin >> str;
        num = count(str.begin(), str.end(), '.'); // count统计.的数目
        len = str.find("/") != -1 ? atoi(str.substr(str.find("/") + 1).c_str()) : (num + 1) * 8; // 计算len
        str = str.find("/") != -1 ? str.substr(0, str.find("/")) : str;  // 分离截取除ip
        for (int j = 0; j < 3 - num; j++)  // 补全.0
            str += ".0";
        stringstream ss(str);
        while (getline(ss, singleStr, '.'))  // 分离转换成4个8位二进制的ip
            newStr += toTwo(atoi(singleStr.c_str()));
        lt.insert(lt.end(), IP(newStr, len));
    }
    lt.sort();
    for (list<IP>::iterator cur = lt.begin(), next; cur != lt.end();) // 第二步从小到大合并
    {
        next = cur;
        if (++next == lt.end()) // next指向下一个元素，同时判断是否结束
            break;
        for (i = 0; i < cur->len; i++) // 高位(长为len)有不同即不是子集
            if (cur->ip[i] != next->ip[i])
                break;
        if (i == cur->len)
            lt.erase(next);
        else
            cur++;
    }
    for (list<IP>::iterator cur = lt.begin(), next; cur != lt.end();) //第三部同级合并
    {
        next = cur;
        if (++next == lt.end())
            break;
        if (cur->len == next->len && cur->ip[cur->len - 1] == '0') // a,b前缀长度相同且a'合法(注:a'与a的ip相同)
        {
            for (i = 0; i < cur->len - 1; i++) // a并b=a'等价于判断b是否是a的子集，故同第二步的方法(注:a'与a的ip相同)
                if (cur->ip[i] != next->ip[i])
                    break;
            if (i == cur->len - 1)
            {
                lt.erase(next);        // 删除b
                cur->len -= 1;         // 用a'代替a，相当于删除a插入a'(注:a'比a的前缀len小1)
                if (cur != lt.begin()) // 如果a'前还存在元素，从其前一个考虑
                {
                    cur--;
                    continue;
                }
            }
        }
        cur++;
    }
    for (auto it : lt) // 第四步输出结果
    {
        for (int i = 7; i < 32; i += 8)
        {
            int temp = 0;
            for (int j = i - 7; j <= i; j++) // 每8位转换为10进制
                temp = temp * 2 + it.ip[j] - '0';
            cout << temp << (i != 31 ? "." : "");
        }
        cout << "/" << it.len << endl;
    }
    return 0;
}