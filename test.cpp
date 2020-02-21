#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> ans;

int main()
{
    //读入Markdown文本
    string s;
    while (getline(cin, s))
    {
        ans.push_back(s);
    }
    // 1.处理 强调
    for (int i = 0, cnt = 0; i < ans.size(); i++)
        for (int j = 0; j < ans[i].length(); j++)
            if (ans[i][j] == '_')
            {
                cnt++;
                s = (cnt % 2) ? ("<em>") : ("</em>");
                ans[i].insert(j + 1, s);
                ans[i].erase(j, 1);
            }
    // 2.处理 超链接
    for (int i = 0; i < ans.size(); i++)
        for (int j = 0; j < ans[i].length(); j++)
        {
            int pos1 = ans[i].find("[", j);
            int pos2 = ans[i].find("]", j + 1);
            int pos3 = ans[i].find(")", j + 3);
            if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos)
                break;
            string text, link;
            text = ans[i].substr(pos1 + 1, pos2 - pos1 - 1);
            link = ans[i].substr(pos2 + 2, pos3 - pos2 - 2);
            s = "<a href=\"" + link + "\">" + text + "</a>";
            ans[i].erase(pos1, pos3 - pos1 + 1);
            ans[i].insert(pos1, s);
        }
    // 3.
    for (int i = 0; i < ans.size(); i++)
    {
        if (ans[i] == "")
            continue;
        if (ans[i][0] == '#')
        { //处理标题
            int cnt = 0, j;
            while (ans[i][cnt++] == '#')
                ;
            //截取标题
            cnt--;
            for (j = 1; j < ans[i].length(); j++)
                if (ans[i][j - 1] == ' ' && ans[i][j] != ' ')
                    break;
            ans[i] = ans[i].substr(j);
            ans[i] = "<h>" + ans[i] + "</h>";
            char c = cnt + '0';
            ans[i].insert(2, 1, c);
            int len = ans[i].length() - 1;
            ans[i].insert(len, 1, c);
        }
        else if (ans[i][0] == '*')
        { //处理列表
            //列表第一行是i,找到最后一行
            int j = i + 1;
            for (; j < ans.size() && ans[j][0] == '*'; j++)
                ;
            j--;                                      //j是列表的最后一行
            ans.insert(ans.begin() + j + 1, "</ul>"); //考虑到插入操作对迭代器的影响故从后往前插
            ans.insert(ans.begin() + i, "<ul>");
            //现在列表处于 i+1 和 j+1之间了
            for (int k = i + 1; k <= j + 1; k++)
            {
                int pos;
                for (pos = 1; pos < ans[k].length(); pos++)
                    if (ans[k][pos - 1] = ' ' && ans[k][pos] != ' ')
                        break;
                ans[k] = ans[k].substr(pos);
                ans[k] = "<li>" + ans[k] + "</li>";
            }
            i = j + 2;
        }
        else
        {
            int pos = i + 1;
            for (; pos < ans.size() && ans[pos] != "" && ans[pos][0] != '#' && ans[pos][0] != '*'; pos++)
                ;
            pos--;
            ans[i] = "<p>" + ans[i];
            ans[pos] += "</p>";
            i = pos;
        }
    }
    for (int i = 0; i < ans.size(); i++)
        if (ans[i] != "")
            cout << ans[i] << endl;
    return 0;
}