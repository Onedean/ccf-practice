/* 
问题描述
　　授权 (authorization) 是各类业务系统不可缺少的组成部分，系统用户通过授权机制获得系统中各个模块的操作权限。
　　本题中的授权机制是这样设计的：每位用户具有若干角色，每种角色具有若干权限。例如，用户 david 具有 manager 
    角色，manager 角色有 crm:2 权限，则用户 david 具有 crm:2 权限，也就是 crm 类权限的第 2 等级的权限。
　　具体地，用户名和角色名称都是由小写字母组成的字符串，长度不超过 32。权限分为分等级权限和不分等级权限两大类。
    分等级权限由权限类名和权限等级构成，中间用冒号“:”分隔。其中权限类名也是由小写字母组成的字符串，长度不超过 
    32。权限等级是一位数字，从 0 到 9，数字越大表示权限等级越高。系统规定如果用户具有某类某一等级的权限，那么
    他也将自动具有该类更低等级的权限。例如在上面的例子中，除 crm:2 外，用户 david 也具有 crm:1 和 crm:0 权限。
    不分等级权限在描述权限时只有权限类名，没有权限等级（也没有用于分隔的冒号）。
　　给出系统中用户、角色和权限的描述信息，你的程序需要回答多个关于用户和权限的查询。查询可分为以下几类：
　　* 不分等级权限的查询：如果权限本身是不分等级的，则查询时不指定等级，返回是否具有该权限；
　　* 分等级权限的带等级查询：如果权限本身分等级，查询也带等级，则返回是否具有该类的该等级权限；
　　* 分等级权限的不带等级查询：如果权限本身分等级，查询不带等级，则返回具有该类权限的等级；如果不具有该类的任何
      等级权限，则返回“否”。
输入格式
　　输入第一行是一个正整数 p，表示不同的权限类别的数量。紧接着的 p 行被称为 P 段，每行一个字符串，描述各个权限。
    对于分等级权限，格式为 <category>:<level>，其中 <category> 是权限类名，<level> 是该类权限的最高等级。
    对于不分等级权限，字符串只包含权限类名。
　　接下来一行是一个正整数 r，表示不同的角色数量。紧接着的 r 行被称为 R 段，每行描述一种角色，格式为
　　<role> <s> <privilege 1> <privilege 2> ... <privilege s>
　　其中 <role> 是角色名称，<s> 表示该角色具有多少种权限。后面 <s> 个字符串描述该角色具有的权限，格式同 P 段。
　　接下来一行是一个正整数 u，表示用户数量。紧接着的 u 行被称为 U 段，每行描述一个用户，格式为
　　<user> <t> <role 1> <role 2> ... <role t>
　　其中 <user> 是用户名，<t> 表示该用户具有多少种角色。后面 <t> 个字符串描述该用户具有的角色。
　　接下来一行是一个正整数 q，表示权限查询的数量。紧接着的 q 行被称为 Q 段，每行描述一个授权查询，格式为
     <user> <privilege>，表示查询用户 <user> 是否具有 <privilege> 权限。如果查询的权限是分等级权限，则
    查询中的 <privilege> 可指定等级，表示查询该用户是否具有该等级的权限；也可以不指定等级，表示查询该用户
    具有该权限的等级。对于不分等级权限，只能查询该用户是否具有该权限，查询中不能指定等级。
输出格式
　　输出共 q 行，每行为 false、true，或者一个数字。false 表示相应的用户不具有相应的权限，true 表示相应的
    用户具有相应的权限。对于分等级权限的不带等级查询，如果具有权限，则结果是一个数字，表示该用户具有该权限
    的（最高）等级。如果用户不存在，或者查询的权限没有定义，则应该返回 false。
样例输入
3
crm:2
git:3
game
4
hr 1 crm:2
it 3 crm:1 git:1 game
dev 2 git:3 game
qa 1 git:2
3
alice 1 hr
bob 2 it qa
charlie 1 dev
9
alice game
alice crm:2
alice git:0
bob git
bob poweroff
charlie game
charlie crm
charlie git:3
malice game
样例输出
false
true
false
2
false
true
false
true
false
样例说明
　　样例输入描述的场景中，各个用户实际的权限如下：
　　* 用户 alice 具有 crm:2 权限
　　* 用户 bob 具有 crm:1、git:2 和 game 权限
　　* 用户 charlie 具有 git:3 和 game 权限
　　* 用户 malice 未描述，因此不具有任何权限
评测用例规模与约定
　　评测用例规模：
　　* 1 ≤ p, r, u ≤ 100
　　* 1 ≤ q ≤ 10?000
　　* 每个用户具有的角色数不超过 10，每种角色具有的权限种类不超过 10
　　约定：
　　* 输入保证合法性，包括：
　　1) 角色对应的权限列表（R 段）中的权限都是之前（P 段）出现过的，权限可以重复出现，如果带等级的权限
        重复出现，以等级最高的为准
　　2) 用户对应的角色列表（U 段）中的角色都是之前（R 段）出现过的，如果多个角色都具有某一分等级权限，
        以等级最高的为准
　　3) 查询（Q 段）中的用户名和权限类名不保证在之前（U 段和 P 段）出现过
　　* 前 20% 的评测用例只有一种角色
　　* 前 50% 的评测用例权限都是不分等级的，查询也都不带等级
 */
#include <iostream>
#include <string>
using namespace std;
struct Power
{
    string powerName;
    int level;
};
struct Node
{
    string name;
    struct Power power[100];
    int len;
} role[100], user[100];
int main()
{
    int p, r, s, u, t, q, tempNum;
    string str, nameStr, tempName;
    cin >> p;
    for (int i = 0; i < p; i++) // 输入权限定义，题目保证数据正确，这里数据无用模拟输入即可
        cin >> str;
    cin >> r;
    for (int i = 0; i < r; i++) // 输入角色定义
    {
        cin >> role[i].name >> s;
        role[i].len = s;
        for (int j = 0; j < s; j++)
        {
            cin >> str;
            if (str.find(':') == -1)
            {
                role[i].power[j].powerName = str;
                role[i].power[j].level = -1;
            }
            else
            {
                role[i].power[j].powerName = str.substr(0, str.size() - 2);
                role[i].power[j].level = str[str.size() - 1] - '0';
            }
        }
    }
    cin >> u;
    for (int i = 0; i < u; i++) // 输入用户定义
    {
        int index = 0;
        cin >> user[i].name >> t;
        for (int j = 0; j < t; j++) // 对应赋权限
        {
            cin >> str;
            for (int k = 0; k < r; k++)
                if (str == role[k].name)
                    for (int l = 0; l < role[k].len; l++, index++)
                    {
                        user[i].power[index].powerName = role[k].power[l].powerName;
                        user[i].power[index].level = role[k].power[l].level;
                    }
        }
        user[i].len = index;
    }
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int flag = 0;
        cin >> str >> nameStr;
        if (nameStr.find(':') == -1)
        {
            tempName = nameStr;
            tempNum = -2;
        }
        else
        {
            tempName = nameStr.substr(0, nameStr.size() - 2);
            tempNum = nameStr[nameStr.size() - 1] - '0';
        }
        for (int j = 0; j < u; j++)
            if (str == user[j].name)
                for (int k = 0; k < user[j].len; k++)
                    if (user[j].power[k].powerName == tempName && user[j].power[k].level >= tempNum)
                    {
                        tempNum = user[j].power[k].level;
                        flag = 1; // 标记查找到了
                    }
        if (nameStr.find(':') == -1 && tempNum > -1) // 不带等级查询
            cout << tempNum << endl;
        else if (nameStr.find(':') == -1 && tempNum == -1)
            cout << "true" << endl;
        else if (nameStr.find(':') == -1 && tempNum == -2)
            cout << "false" << endl;
        else if (nameStr.find(':') != -1 && flag) // 带等级查询
            cout << "true" << endl;
        else
            cout << "false" << endl;
    }
}