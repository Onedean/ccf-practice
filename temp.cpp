#include <bits/stdc++.h>
using namespace std;
using llg = long long;
llg n, m, k, r, ans = 0;
vector<array<llg, 2>> routers(205);  //存储路由器的坐标
int main() {
    cin >> n >> m >> k >> r;
    for (int i = 0; i < n + m; ++i) {
        cin >> routers[i][0] >> routers[i][1];
    }
    queue<array<llg, 3>> q;  // array<llg, 3>分别存储routers下标,经过的路由器个数,经过的增设路由器个数
    bitset<205> inQueue;  //标记结点是否入队
    q.push({0, 0, 0});
    inQueue[0] = true;
    while (not q.empty()) {
        auto i = q.front();
        q.pop();
        if (i[0] == 1) {
            ans = i[1] - 1;
            break;
        }
        const auto& v = routers[i[0]];
        for (int j = 0; j < n + m; ++j) {
            if (not inQueue[j] and hypot(routers[j][0] - v[0], routers[j][1] - v[1]) <= r * 1.0 and
                (j < n or i[2] < k)) {  //该结点未入过队且距离<=r且经过的增设路由器个数<k
                q.push({j, i[1] + 1, i[2] + (j < n ? 0 : 1)});
                inQueue[j] = true;
            }
        }
    }
    cout << ans;
    return 0;
}