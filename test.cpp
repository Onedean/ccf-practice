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
    { //�����ƶ�
        dfs(x, y + 1, c);
    }
    if (judge(x + 1, y))
    { //�����ƶ�
        dfs(x + 1, y, c);
    }
    if (judge(x, y - 1))
    { //�����ƶ�
        dfs(x, y - 1, c);
    }
    if (judge(x - 1, y))
    { //�����ƶ�
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
                        ֮�����Ǽ� a[j][x1] == '+'�����������10�֣����ݣ�����������������
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
				Ҫ�������տ�ʼ����ÿ�γ�ʼ��0�ˣ����ֻ����50��
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