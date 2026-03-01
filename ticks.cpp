#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) cin >> grid[i];

        vector<vector<int>> upLeft(n, vector<int>(m, 0));
        vector<vector<int>> upRight(n, vector<int>(m, 0));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '*') {
                    int ul = 1;
                    int ur = 1;
                    if (i > 0 && j > 0) ul += upLeft[i - 1][j - 1];
                    if (i > 0 && j + 1 < m) ur += upRight[i - 1][j + 1];
                    upLeft[i][j] = ul;
                    upRight[i][j] = ur;
                }
            }
        }

        vector<vector<bool>> covered(n, vector<bool>(m, false));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] != '*') continue;
                int maxSize = min(upLeft[i][j], upRight[i][j]) - 1;
                if (maxSize < k) continue;
                for (int h = 0; h <= maxSize; ++h) {
                    covered[i - h][j - h] = true;
                    covered[i - h][j + h] = true;
                }
            }
        }

        bool ok = true;
        for (int i = 0; i < n && ok; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '*' && !covered[i][j]) {
                    ok = false;
                    break;
                }
            }
        }

        cout << (ok ? "YES\n" : "NO\n");
    }

    return 0;
}

