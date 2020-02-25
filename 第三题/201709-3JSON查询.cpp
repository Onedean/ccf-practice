/* 
问题描述
　　JSON (JavaScript Object Notation) 是一种轻量级的数据交换格式，可以用来描述半结构化的数据。JSON 格式
    中的基本单元是值 (value)，出于简化的目的本题只涉及 2 种类型的值：
　　* 字符串 (string)：字符串是由双引号 " 括起来的一组字符（可以为空）。如果字符串的内容中出现双引号 "，在
        双引号前面加反斜杠，也就是用 \" 表示；如果出现反斜杠 \，则用两个反斜杠 \\ 表示。反斜杠后面不能出现
         " 和 \ 以外的字符。例如：""、"hello"、"\"\\"。
　　* 对象 (object)：对象是一组键值对的无序集合（可以为空）。键值对表示对象的属性，键是属性名，值是属性的内容。
        对象以左花括号 { 开始，右花括号 } 结束，键值对之间以逗号 , 分隔。一个键值对的键和值之间以冒号 : 分隔。
        键必须是字符串，同一个对象所有键值对的键必须两两都不相同；值可以是字符串，也可以是另一个对象。例如：{}、
        {"foo": "bar"}、{"Mon": "weekday", "Tue": "weekday", "Sun": "weekend"}。
　　除了字符串内部的位置，其他位置都可以插入一个或多个空格使得 JSON 的呈现更加美观，也可以在一些地方换行，不会影
    响所表示的数据内容。例如，上面举例的最后一个 JSON 数据也可以写成如下形式。
　　{
　　"Mon": "weekday",
　　"Tue": "weekday",
　　"Sun": "weekend"
　　}
　　给出一个 JSON 格式描述的数据，以及若干查询，编程返回这些查询的结果。
输入格式
　　第一行是两个正整数 n 和 m，分别表示 JSON 数据的行数和查询的个数。
　　接下来 n 行，描述一个 JSON 数据，保证输入是一个合法的 JSON 对象。
　　接下来 m 行，每行描述一个查询。给出要查询的属性名，要求返回对应属性的内容。需要支持多层查询，各层的属性名之间
    用小数点 . 连接。保证查询的格式都是合法的。
输出格式
　　对于输入的每一个查询，按顺序输出查询结果，每个结果占一行。
　　如果查询结果是一个字符串，则输出 STRING <string>，其中 <string> 是字符串的值，中间用一个空格分隔。
　　如果查询结果是一个对象，则输出 OBJECT，不需要输出对象的内容。
　　如果查询结果不存在，则输出 NOTEXIST。
样例输入
10 5
{
"firstName": "John",
"lastName": "Smith",
"address": {
"streetAddress": "2ndStreet",
"city": "NewYork",
"state": "NY"
},
"esc\\aped": "\"hello\""
}
firstName
address
address.city
address.postal
esc\aped
样例输出
STRING John
OBJECT
STRING NewYork
NOTEXIST
STRING "hello"
评测用例规模与约定
　　n ≤ 100，每行不超过 80 个字符。
　　m ≤ 100，每个查询的长度不超过 80 个字符。
　　字符串中的字符均为 ASCII 码 33-126 的可打印字符，不会出现空格。所有字符串都不是空串。
　　所有作为键的字符串不会包含小数点 .。查询时键的大小写敏感。
　　50%的评测用例输入的对象只有 1 层结构，80%的评测用例输入的对象结构层数不超过 2 层。举例来说，{"a": "b"} 是
    一层结构的对象，{"a": {"b": "c"}} 是二层结构的对象，以此类推。
 */
//正则+dfs处理
#include <iostream>
#include <map>
#include <regex>
using namespace std;
map<string, string> mp;
stringstream ss;
bool dfs(string key) // 注意嵌套未知层数故用while判断条件则返回是bool型
{
    string str;
    ss >> str;      //以空格分割流出到str
    if (str == "}") // 结束递归条件
        return false;
    if (str != "{") // 如果该键对应是字符值
    {
        string value = str.substr(1, str.rfind('"') - 1); // 获取引号内内容
        if (str.back() != ':')
            mp[key] = value; // 是字符,直接存储
        else
            dfs(key == "" ? value : key + "." + value); // 是键,此时没进入对象内，单次递归调用判断接下来是对象还是字符
    }
    else // 如果该键对应是对象值，则递归调用
    {
        if (key != "")
            mp[key] = "OBJECT";
        while (dfs(key)) // 此时进入对象内，嵌套层数位置用while递归调用
            ;
    }
    return true;
}
int main()
{
    int n, m;
    string str, json;
    cin >> n >> m;
    getchar();
    while (n--)
    {
        getline(cin, str);
        json += str;
    }
    json = regex_replace(json, regex(" "), "");
    json = regex_replace(json, regex("\\\\\""), "\"");   // 2和3步正则不可颠倒,注意这种情况\\"
    json = regex_replace(json, regex("\\\\\\\\"), "\\"); // c++中\\表示\,正则regex()中\\a表示a(其中a为特殊字符如\或下面的{)
    json = regex_replace(json, regex(","), ", ");
    json = regex_replace(json, regex(":"), ": ");
    json = regex_replace(json, regex("\\{"), " { "); // {不可直接匹配
    json = regex_replace(json, regex("},?"), " } "); // 注意对象里}后,可能有或无
    ss << json;                                      // 将json塞入ss流中
    dfs("");                                         // 传入键名,假定整体对象键名用空字符串代替
    while (m--)
    {
        cin >> str;
        if (mp.find(str) == mp.end())
            cout << "NOTEXIST" << endl;
        else if (mp[str] == "OBJECT")
            cout << "OBJECT" << endl;
        else
            cout << "STRING " << mp[str] << endl;
    }
    return 0;
}