#include <bits/stdc++.h>
using namespace std;

void solve() {
    int l, n, m;
    cin >> l >> n >> m;

    vector<int> a(l + 1);
    for (int i = 1; i <= l; ++i) {
        cin >> a[i];
    }

    vector<vector<int>> b(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> b[i][j];
        }
    }

    vector<vector<char>> next(n + 2, vector<char>(m + 2, 0));
    vector<vector<char>> cur(n + 2, vector<char>(m + 2, 0));

    for (int idx = l; idx >= 1; --idx) {
        for (int i = n; i >= 1; --i) {
            for (int j = m; j >= 1; --j) {
                char canWinByChoosingHere = (b[i][j] == a[idx] && next[i + 1][j + 1] == 0);
                cur[i][j] = canWinByChoosingHere || cur[i + 1][j] || cur[i][j + 1];
            }
        }

        for (int i = 1; i <= n + 1; ++i) {
            cur[i][m + 1] = 0;
        }
        for (int j = 1; j <= m + 1; ++j) {
            cur[n + 1][j] = 0;
        }

        swap(cur, next);
        for (int i = 1; i <= n; ++i) {
            fill(cur[i].begin(), cur[i].end(), 0);
        }
    }

    cout << (next[1][1] ? 'T' : 'N') << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

