#include <bits/stdc++.h>
using namespace std;
int m, n, q;
char a[101][101];
int mark[101][101];

bool judge(int x, int y)
{
    if (x < 0 || y < 0 || x > m || y > n)
    {
        return false;
    }
    else if (mark[y][x] == 1)
    {
        return false;
    }
    else if (a[y][x] == '+' || a[y][x] == '|' || a[y][x] == '-')
    {
        return false;
    }
    else
    {
        return true;
    }
}

void dfs(int x, int y, char c)
{
    a[y][x] = c;
    mark[y][x] = 1;
    if (judge(x, y + 1))
    { //向下移动
        dfs(x, y + 1, c);
    }
    if (judge(x + 1, y))
    { //向右移动
        dfs(x + 1, y, c);
    }
    if (judge(x, y - 1))
    { //向上移动
        dfs(x, y - 1, c);
    }
    if (judge(x - 1, y))
    { //向左移动
        dfs(x - 1, y, c);
    }
}

int main()
{
    cin >> m >> n >> q;
    memset(a, '.', sizeof(a));

    for (int i = 0; i < q; i++)
    {
        int y, x1, y1;
        cin >> y;
        if (y == 0)
        {
            int x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            y1 = n - 1 - y1;
            y2 = n - 1 - y2;
            if (x1 == x2)
            {
                for (int j = min(y1, y2); j <= max(y1, y2); j++)
                {
                    /*
                        之后忘记加 a[j][x1] == '+'这个条件，扣10分，蓝瘦，啊啊啊啊啊啊啊啊
					*/
                    a[j][x1] = a[j][x1] == '-' || a[j][x1] == '+' ? '+' : '|';
                }
            }
            else
            {
                for (int j = min(x1, x2); j <= max(x1, x2); j++)
                {
                    a[y1][j] = a[y1][j] == '|' || a[y1][j] == '+' ? '+' : '-';
                }
            }
        }
        else if (y == 1)
        {
            char c;
            cin >> x1 >> y1 >> c;
            /*
				要命处，刚开始忘记每次初始化0了，结果只能拿50分
			*/
            memset(mark, 0, sizeof(mark));
            dfs(x1, n - 1 - y1, c);
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << a[i][j];
        }
        cout << endl;
    }
    return 0;
}
