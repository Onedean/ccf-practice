/* 
问题描述
　　成成最近在搭建一个网站，其中一些页面的部分内容来自数据库中不同的数据记录，
    但是页面的基本结构是相同的。例如，对于展示用户信息的页面，当用户为 Tom 时，网页的源代码是
<!DOCTYPE html>
<html>
    <head>
        <title>User Tom</head>
    </head>
    <body>
        <h1>Tom</h1>
        <p>Email: <a href="mailto:tom@example.com">tom@example.com</a></p>
    </body>
</html>
　　而当用户为 Jerry 时，网页的源代码是
<!DOCTYPE html>
<html>
    <head>
        <title>User Jerry</head>
    </head>
    <body>
        <h1>Jerry</h1>
        <p>Email: <a href="mailto:jerry@example.com">jerry@example.com</a></p>
    </body>
</html>
　　这样的例子在包含动态内容的网站中还有很多。为了简化生成网页的工作，成成觉得他需要引入一套模板生成系统。
　　模板是包含特殊标记的文本。成成用到的模板只包含一种特殊标记，格式为 {{ VAR }}，其中 VAR 是一个变量。该标记在模板生成时会被变量 VAR 的值所替代。例如，如果变量 name = "Tom"，则 {{ name }} 会生成 Tom。具体的规则如下：
　　·变量名由大小写字母、数字和下划线 (_) 构成，且第一个字符不是数字，长度不超过 16 个字符。
　　·变量名是大小写敏感的，Name 和 name 是两个不同的变量。
　　·变量的值是字符串。
　　·如果标记中的变量没有定义，则生成空串，相当于把标记从模板中删除。
　　·模板不递归生成。也就是说，如果变量的值中包含形如 {{ VAR }} 的内容，不再做进一步的替换。
输入格式
　　输入的第一行包含两个整数 m, n，分别表示模板的行数和模板生成时给出的变量个数。
　　接下来 m 行，每行是一个字符串，表示模板。
　　接下来 n 行，每行表示一个变量和它的值，中间用一个空格分隔。值是字符串，用双引号 (") 括起来，内容可包含除双引号以外的任意可打印 ASCII 字符（ASCII 码范围 32, 33, 35-126）。
输出格式
　　输出包含若干行，表示模板生成的结果。
样例输入
11 2
<!DOCTYPE html>
<html>
<head>
<title>User {{ name }}</title>
</head>
<body>
<h1>{{ name }}</h1>
<p>Email: <a href="mailto:{{ email }}">{{ email }}</a></p>
<p>Address: {{ address }}</p>
</body>
</html>
name "David Beckham"
email "david@beckham.com"
样例输出
<!DOCTYPE html>
<html>
<head>
<title>User David Beckham</title>
</head>
<body>
<h1>David Beckham</h1>
<p>Email: <a href="mailto:david@beckham.com">david@beckham.com</a></p>
<p>Address: </p>
</body>
</html>
评测用例规模与约定
　　0 ≤ m ≤ 100
　　0 ≤ n ≤ 100
　　输入的模板每行长度不超过 80 个字符（不包含换行符）。
　　输入保证模板中所有以 {{ 开始的子串都是合法的标记，开始是两个左大括号和一个空格，然后是变量名，结尾是一个空格和两个右大括号。
　　输入中所有变量的值字符串长度不超过 100 个字符（不包括双引号）。
　　保证输入的所有变量的名字各不相同。
 */
#include <iostream>
#include <string>
#include <map>
using namespace std;
int main()
{
    int m, n, pre, pro;
    string temp[100], name, value;
    map<string, string> dict;
    cin >> m >> n;
    getchar();
    for (int i = 0; i < m; i++)
        getline(cin, temp[i]);
    for (int i = 0; i < n; i++)
    {
        cin >> name;
        getline(cin, value);
        dict[name] = value.substr(2, value.size() - 3); //value会读空格,所以从第2位取,去掉 ""3个字符
    }
    for (int i = 0; i < m; i++)
    {
        pre = 0;                                       // 清零上次位置，防止下面不是从头找
        while ((pre = temp[i].find("{{ ", pre)) != -1) // 查找" {{"并判断替换完成条件
        {
            pro = temp[i].find(" }}", pre);                                          //查找" }}"位置
            name = temp[i].substr(pre + 3, pro - pre - 3);                           // 取出{{ xxx }}中的字符
            temp[i].replace(pre, pro - pre + 3, dict.count(name) ? dict[name] : ""); //替换{{ xxx }}中字符xxx
            pre += dict.count(name) ? dict[name].size() : 0;                         // 处理完此次置换后移查找位置
        }
        cout << temp[i] << endl;
    }
    return 0;
}