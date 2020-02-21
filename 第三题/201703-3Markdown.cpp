/* 
　　本题要求由你来编写一个 Markdown 的转换工具，完成 Markdown 文本到 HTML 代码的转换工作。简化起见，
    本题定义的 Markdown 语法规则和转换规则描述如下：
　　●区块：区块是文档的顶级结构。本题的 Markdown 语法有 3 种区块格式。在输入中，相邻两个区块之间用一个
        或多个空行分隔。输出时删除所有分隔区块的空行。
　　○段落：一般情况下，连续多行输入构成一个段落。段落的转换规则是在段落的第一行行首插入 `<p>`，在最后一
        行行末插入 `</p>`。
　　○标题：每个标题区块只有一行，由若干个 `#` 开头，接着一个或多个空格，然后是标题内容，直到行末。`#` 的
        个数决定了标题的等级。转换时，`# Heading` 转换为 `<h1>Heading</h1>`，`## Heading` 转换为 
        `<h2>Heading</h2>`，以此类推。标题等级最深为 6。
　　○无序列表：无序列表由若干行组成，每行由 `*` 开头，接着一个或多个空格，然后是列表项目的文字，直到行末。
        转换时，在最开始插入一行 `<ul>`，最后插入一行 `</ul>`；对于每行，`* Item` 转换为 `<li>Item</li>`。
        本题中的无序列表只有一层，不会出现缩进的情况。
　　●行内：对于区块中的内容，有以下两种行内结构。
　　○强调：`_Text_` 转换为 `<em>Text</em>`。强调不会出现嵌套，每行中 `_` 的个数一定是偶数，且不会连续相邻。
        注意 `_Text_` 的前后不一定是空格字符。
　　○超级链接：`[Text](Link)` 转换为 `<a href="Link">Text</a>`。超级链接和强调可以相互嵌套，但每种格式不会
        超过一层。
输入格式
　　输入由若干行组成，表示一个用本题规定的 Markdown 语法撰写的文档。
输出格式
　　输出由若干行组成，表示输入的 Markdown 文档转换成产生的 HTML 代码。
样例输入
# Hello

Hello, world!
样例输出
<h1>Hello</h1>
<p>Hello, world!</p>

# Heading

## Sub-heading

Paragraphs are separated
by a blank line

Text attribute _italic_.

Bullet list:

* apples
* orange
* pears

A [link](http://example.com).



评测用例规模与约定
　　本题的测试点满足以下条件：
　　●本题每个测试点的输入数据所包含的行数都不超过100，每行字符的个数（包括行末换行符）都不超过100。
　　●除了换行符之外，所有字符都是 ASCII 码 32 至 126 的可打印字符。
　　●每行行首和行末都不会出现空格字符。
　　●输入数据除了 Markdown 语法所需，内容中不会出现 `#`、`*`、`_`、`[`、`]`、`(`、`)`、`<`、`>`、`&` 这些字符。
　　●所有测试点均符合题目所规定的 Markdown 语法，你的程序不需要考虑语法错误的情况。
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main()
{
    string line, str, text, link;
    vector<string> vc;
    while (getline(cin, line))
    {
        vc.push_back(line);
    }
    // 处理行内
    for (int i = 0; i < vc.size(); i++) // 1.处理强调
    {
        int index = 0;
        for (int j = 0; j < vc[i].size(); j++)
            if (vc[i][j] == '_')
            {
                index++;
                str = (index % 2) ? "<em>" : "</em>";
                vc[i].insert(j + 1, str);
                vc[i].erase(j, 1);
            }
    }
    for (int i = 0; i < vc.size(); i++) // 2.处理超链接
        for (int j = 0; j < vc[i].size(); j++)
            if (vc[i][j] == '[')
            {
                text = vc[i].substr(j + 1, vc[i].find(']') - j - 1);
                link = vc[i].substr(vc[i].find('(') + 1, vc[i].find(')') - vc[i].find('(') - 1);
                vc[i].replace(j, vc[i].find(')') - j + 1, "<a href=\"" + link + "\">" + text + "</a>");
            }
    // 处理区块
    for (int i = 0; i < vc.size(); i++)
    {
        if (vc[i] == "")
            continue;
        if (vc[i][0] == '#')
        {
            char len = vc[i].find(' ') > 6 ? '6' : vc[i].find(' ') + '0';
            int j;
            for (j = 1; j < vc[i].size(); j++) // 注意逻辑的运算顺序防止越界
                if (vc[i][j - 1] == ' ' && vc[i][j] != ' ')
                    break;
            vc[i] = "<h>" + vc[i].substr(j) + "</h>";
            vc[i].insert(vc[i].begin() + 2, len);
            vc[i].insert(vc[i].end() - 1, len);
        }
        else if (vc[i][0] == '*')
        {
            int j;
            for (j = i + 1; j < vc.size() && vc[j][0] == '*'; j++) // 注意逻辑的运算顺序防止越界
                ;
            vc.insert(vc.begin() + j, "</ul>"); // 注意先插后面，在插前面
            vc.insert(vc.begin() + i, "<ul>");
            for (int k = i + 1; k <= j; k++) // 注意j相对于整体的变化
            {
                int l;
                for (l = 1; l < vc[k].size(); l++)
                    if (vc[k][l - 1] == ' ' && vc[k][l] != ' ')
                        break;
                vc[k] = "<li>" + vc[k].substr(l) + "</li>";
            }
            i = j + 1; // 注意此时长度改变
        }
        else
        {
            int j;
            for (j = i + 1; j < vc.size() && vc[j] != "" && vc[j][0] != '*' && vc[j][0] != '#'; j++)
                ;
            vc[i] = "<p>" + vc[i];
            vc[j - 1] = vc[j - 1] + "</p>";
            i = j - 1; // 注意更新下标i，否则重复添加p标签
        }
    }
    for (int i = 0; i < vc.size(); i++)
        if (vc[i] != "")
            cout << vc[i] << endl;
    return 0;
}