#include <iostream>
#include <map>
using namespace std;
//one保存key和value，two保存当前层路径和嵌套层路径
map<string, string> one, two;
//处理字符串，去掉反斜杠，参数是i的引用，这样方便遍历
string deal(int &i, string a)
{
    i++;
    string res = "";
    while (1)
    {
        if (a[i] == '"')
            break;
        if (a[i] == '\\')
        {
            res += a[i + 1];
            i++;
        }
        else
            res += a[i];
        i++;
    }
    return res;
}
int main()
{
    int n, m;
    cin >> n >> m;
    getchar();
    //line用来连接输入的每一行，方便处理。name表示当前层的路径
    string line = "", temp, name = "", key = "", value = "";
    //将输入的每一行连接起来，方便处理
    while (n--)
    {
        getline(cin, temp);
        line += temp;
    }
    int len = line.length();
    for (int i = 1; i < len - 1; i++)
    {
        //跳过空格和逗号
        if (line[i] == ' ' || line[i] == ',')
            continue;
        //遇到了}，即一层嵌套的结束，这时候路径应该改成当前层的路径
        else if (line[i] == '}')
            name = two[name];
        //遇到了"，表示要输入key了，输入i的引用，在函数结束后，i便跳到了key的第二个引号上
        else if (line[i] == '"')
            key = deal(i, line);
        //遇到了：，表示要输入value了
        else if (line[i] == ':')
        {
            i++;
            //先去掉多余的空格
            while (line[i] == ' ')
                i++;
            //如果输入的是字符串，先处理，再存到map中
            if (line[i] == '"')
            {
                value = deal(i, line);
                //此时储存的是key的路径，用 . 连接
                one[name + "." + key] = value;
            }
            //如果输入的value是嵌套的对象，就把key的value设为 OBJECT
            else if (line[i] == '{')
            {
                //此时储存的是key的路径，用 . 连接
                one[name + "." + key] = "OBJECT";
                //进入嵌套层前，先将嵌套层的路径和当前层的路径对应起来
                two[name + "." + key] = name;
                //路径改成嵌套层的路径
                name = name + "." + key;
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        getline(cin, temp);
        //因为我们的map中的key的开头都有个 . ，所以查询时先加上
        temp = "." + temp;
        if (one.find(temp) != one.end())
        {
            if (one[temp] == "OBJECT")
                cout << "OBJECT" << endl;
            else
                cout << "STRING " << one[temp] << endl;
        }
        else
            cout << "NOTEXIST" << endl;
    }
    return 0;
}