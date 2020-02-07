/* 
问题描述
　　请你写一个命令行分析程序,用以分析给定的命令行里包含哪些选项。每个命令行由若干个字符串组成,它们之间
    恰好由一个空格分隔。这些字符串中的第一个为该命令行工具的名字,由小写字母组成,你的程序不用对它进行处
    理。在工具名字之后可能会包含若干选项,然后可能会包含一些不是选项的参数。
    选项有两类:带参数的选项和不带参数的选项。一个合法的无参数选项的形式是一个减号后面跟单个小写字母,
    如"-a" 或"-b"。而带参数选项则由两个由空格分隔的字符串构成,前者的格式要求与无参数选项相同,后者则是
    该选项的参数,是由小写字母,数字和减号组成的非空字符串。
　　该命令行工具的作者提供给你一个格式字符串以指定他的命令行工具需要接受哪些选项。这个字符串由若干小写
    字母和冒号组成,其中的每个小写字母表示一个该程序接受的选项。如果该小写字母后面紧跟了一个冒号,它就表
    示一个带参数的选项,否则则为不带参数的选项。例如, "ab:m:" 表示该程序接受三种选项,即"-a"(不带参数),
    "-b"(带参数), 以及"-m"(带参数)。
　　命令行工具的作者准备了若干条命令行用以测试你的程序。对于每个命令行,你的工具应当一直向后分析。当你的
    工具遇到某个字符串既不是合法的选项,又不是某个合法选项的参数时,分析就停止。命令行剩余的未分析部分不
    构成该命令的选项,因此你的程序应当忽略它们。
输入格式
　　输入的第一行是一个格式字符串,它至少包含一个字符,且长度不超过 52。格式字符串只包含小写字母和冒号,保证
    每个小写字母至多出现一次,不会有两个相邻的冒号,也不会以冒号开头。
　　输入的第二行是一个正整数 N(1 ≤ N ≤ 20),表示你需要处理的命令行的个数。
　　接下来有 N 行,每行是一个待处理的命令行,它包括不超过 256 个字符。该命令行一定是若干个由单个空格分隔的
    字符串构成,每个字符串里只包含小写字母,数字和减号。
输出格式
　　输出有 N 行。其中第 i 行以"Case i:" 开始,然后应当有恰好一个空格,然后应当按照字母升序输出该命令行中
    用到的所有选项的名称,对于带参数的选项,在输出它的名称之后还要输出它的参数。如果一个选项在命令行中出现
    了多次,只输出一次。如果一个带参数的选项在命令行中出 现了多次,只输出最后一次出现时所带的参数。
样例输入
albw:x
4
ls -a -l -a documents -b
ls
ls -w 10 -x -w 15
ls -a -b -c -d -e -l
样例输出
Case 1: -a -l
Case 2:
Case 3: -w 15 -x
Case 4: -a -b
 */
#include <iostream>
#include <string>
using namespace std;
int main()
{
    string command, str, newStr;
    int n, hashTable[26] = {0};
    cin >> command;
    for (int i = 0; i < command.length(); i++)
    {
        if (command[i] != ':' && command[i + 1] != ':')
            hashTable[command[i] - 'a'] = 1;
        else
        {
            hashTable[command[i] - 'a'] = 2;
            i++;
        }
    }
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> str;
        newStr="";

        cout << "Case " << i << ": " << endl;
    }
    return 0;
}

/* 
 
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
 
using namespace std;
 
const int N = 256;
 
char delimiter[] = " ";
 
void spilt(vector<string>& v, char *s, char *t)
{
    char *sp;
 
    sp = strtok(s, t);
    while(sp) {
         v.push_back(sp);
        sp = strtok(NULL, t);
    }
}
 
void mygetline(char *pc)
{
    char c;
 
    while((c=getchar()) != '\n' && c !=EOF)
        *pc++ = c;
    *pc = '\0';
}
 
int main()
{
    string format;
    char s[N+1];
    int n;
 
    // 输入数据：格式和整数n
    cin >> format >> n;
    getchar();
 
    // 输入n行命令行进行处理
    for(int i=1; i<=n; i++) {
        vector<string> sv;
        map<string, string> m;
 
        // 输入命令行
        mygetline(s);
 
        // 切分命令行：命令和各个参数分开
        spilt(sv, s, delimiter);
 
        // 处理各个参数，放入map变量ｍ中
        for(int j=1; j<(int)sv.size(); j++) {
            if(sv[j].size() == 2 && sv[j][0] == '-') { // 判断是否是选项，选项则处理
                // 选项在格式中未找到则出错结束
                int pos = format.find(sv[j][1]);
                if(pos == -1)
                    break;
 
                // 选项未出现过则添加
                if(m.find(sv[j]) == m.end())
                    m[sv[j]] = "";
 
                // 更新参数：后出现优先
                if(format[pos+1] == ':' && j+1 < (int)sv.size()) {
                    m[sv[j]] = sv[j+1];
                    j++;
                }
            } else
                break;
        }
 
        // 输出结果
        cout << "Case " << i << ":";
        for(map<string,string>::iterator iter=m.begin(); iter!=m.end(); iter++) {
            cout << " " << iter->first;
            if(iter->second != "")
                cout << " " << iter->second;
        }
        cout << endl;
    }
 
    return 0;
}
 */