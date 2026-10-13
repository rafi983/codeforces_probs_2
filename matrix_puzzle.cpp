#include <bits/stdc++.h>
using namespace std;

int m;
vector<vector<int>> bit;

void add(int i, int j, int v) {
    for (int x = i; x <= m; x += x & -x)
        for (int y = j; y <= m; y += y & -y) bit[x][y] += v;
}

int pref(int i, int j) {
    int s = 0;
    for (int x = i; x > 0; x -= x & -x)
        for (int y = j; y > 0; y -= y & -y) s += bit[x][y];
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<vector<long long>> d(n + 2, vector<long long>(n + 2, 0));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) {
                long long v;
                cin >> v;
                d[i][j] = -v;
            }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) {
                long long v;
                cin >> v;
                d[i][j] += v;
            }
        // e[i][j] is the mixed difference of the 2x2 block at (i,j); matchable iff all are 0
        m = n - 1;
        vector<vector<long long>> e(m + 2, vector<long long>(m + 2, 0));
        bit.assign(m + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= m; ++j) {
                e[i][j] = d[i][j] - d[i + 1][j] - d[i][j + 1] + d[i + 1][j + 1];
                bit[i][j] = e[i][j] != 0;
            }
        // prefix sums in place, then convert to a BIT in O(m^2)
        vector<vector<int>> P(m + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= m; ++j)
                P[i][j] = bit[i][j] + P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1];
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= m; ++j) {
                int li = i & -i, lj = j & -j;
                bit[i][j] = P[i][j] - P[i - li][j] - P[i][j - lj] + P[i - li][j - lj];
            }

        auto upd = [&](int i, int j, long long dv) {
            if (i < 1 || j < 1 || i > m || j > m) return;
            bool was = e[i][j] != 0;
            e[i][j] += dv;
            bool now = e[i][j] != 0;
            if (was != now) add(i, j, now ? 1 : -1);
        };

        while (q--) {
            char ch;
            cin >> ch;
            if (ch == 'U') {
                int r1, c1, r2, c2;
                long long x;
                cin >> r1 >> c1 >> r2 >> c2 >> x;
                x = -x;
                upd(r1 - 1, c1 - 1, x);
                upd(r1 - 1, c2, -x);
                upd(r2, c1 - 1, -x);
                upd(r2, c2, x);
            } else {
                int r1, c1, r2, c2;
                cin >> r1 >> c1 >> r2 >> c2;
                if (r1 == r2 || c1 == c2) {
                    cout << "Yes\n";
                    continue;
                }
                int cnt = pref(r2 - 1, c2 - 1) - pref(r1 - 1, c2 - 1) - pref(r2 - 1, c1 - 1) + pref(r1 - 1, c1 - 1);
                cout << (cnt == 0 ? "Yes" : "No") << '\n';
            }
        }
    }
    return 0;
}
