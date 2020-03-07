/* 
表达式 = 表达式
系数1&化学式1 + 系数2&化学式2 + … + 系数n&化学式n = 系数1&化学式1 + 系数2&化学式2 + … + 系数m&化学式m
化学式 = 项1&系数1 & 项2&系数2 & … 项n&系数n
项 = 元素|(化学式)
元素 = 大写字母 | 大写字母 & 小写字母

实际操作单个对象：
外侧系数（若无为1） + 化学式【元素（大写字母或大加小写字母） 或 化学式 + 内层系数（若无为1）】
 */

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
using namespace std;
map<string, int> mp;
typedef pair<string, int> Elem;
int toNumber(string str, int &pos)
{
    int num = 0;
    while (isdigit(str[pos]))
        num = num * 10 + str[pos++] - '0';
    return num;
}
void count(string str, int index)
{
    int pos = 0;
    vector<Elem> vc;
    if (isdigit(str[pos]))
        index *= toNumber(str, pos); // 算出化学式的最外层系数index
    while (pos < str.size())
    {
        if (isdigit(str[pos]))
        {
            int num = toNumber(str, pos);
            int i = vc.size() - 1;
            if (vc[i].first == ")") // 若当前元素为)则匹配到化学式即()内内容，化学式内元素皆乘系数
            {
                vc[i].first = "used";
                while (vc[--i].first != "(")
                    vc[i].second *= num;
                vc[i].first = "used";
            }
            else
                vc[i].second *= num; // 否则仅匹配到那个元素乘系数
        }
        else if (str[pos] == '(')
        {
            vc.push_back(Elem("(", 0));
            pos++;
        }
        else if (str[pos] == ')')
        {
            vc.push_back(Elem(")", 0));
            if (!isdigit(str[++pos]))
                str.insert(pos, "1"); //若')'后面没有数字,则添加'1',保证所有都是')'数字结尾，统一处理
        }
        else if (isupper(str[pos]))
        {
            string name = "";
            name += str[pos++];
            if (islower(str[pos])) // 若后面有小写字母则连接当成一个原子
                name += str[pos++];
            vc.push_back(Elem(name, 1)); // 默认值为1
        }
    }
    for (int i = 0; i < vc.size(); i++)
        mp[vc[i].first] += vc[i].second * index;
}
int main()
{
    int n;
    string str, formula;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> str;
        mp.clear(); //勿忘清空mp
        stringstream s1(str.substr(0, str.find('='))), s2(str.substr(str.find('=') + 1));
        while (getline(s1, formula, '+'))
            count(formula, 1);
        while (getline(s2, formula, '+'))
            count(formula, -1);
        map<string, int>::iterator it;
        for (it = mp.begin(); it != mp.end(); it++)
            if (it->second != 0)
                break;
        cout << (it != mp.end() ? 'N' : 'Y') << endl;
    }
    return 0;
}