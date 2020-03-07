#include <iostream>
#include <vector>
#include <regex>
using namespace std;
int main()
{
    int n, m;
    string p, r;
    vector<pair<string, regex>> vc, trans = {{"([^/]+)", regex("<str>")}, {"([0-9]+)", regex("<int>")}, {"(.+)", regex("<path>")}}; // 注意这里匹配内容加括号，后面匹配成功的result以()为分界匹配的内容数量
    cin >> n >> m;
    while (n--) // 将待映射url规则转换为正则url
    {
        cin >> p >> r;
        for (auto i : trans)
            p = regex_replace(p, i.second, i.first);
        vc.push_back({r, regex(p)});
    }
    smatch result; // 用于存放匹配成功的结果
    while (m--)
    {
        cin >> p;
        for (auto i : vc)
        {
            if (regex_match(p, result, i.second))
            {
                cout << i.first;                        // 匹配成功输出规则名
                for (int j = 1; j < result.size(); j++) //result[0]表示匹配的全部内容，result[i]表示匹配内容中的第i个组（即第i个括号中的内容）
                {
                    string tempStr = result[j];
                    while (tempStr[0] == '0')
                        tempStr.erase(0, 1);
                    cout << ' ' << tempStr;
                }
                cout << endl;
                goto out;
            }
        }
        cout << "404" << endl;
    out:;
    }
}

/*
5 5
/articles/2003/ special_case_2003
/articles/<int>/ year_archive
/articles/<int>/<int>/ month_archive
/articles/<int>/<int>/<str>/ article_detail
/static/<path> static_serve
/articles/2004/
/articles/1985/09/aloha/
/articles/hello/
/static/js/jquery.js
/articles/10/25/0aaa/
 */