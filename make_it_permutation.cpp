#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<array<int, 3>> ops;
        ops.reserve(2 * n);

        for (int i = 1; i <= n; ++i) {
            if (i > 1) {
                ops.push_back({i, 1, i});
            }
            if (i < n) {
                ops.push_back({i, i + 1, n});
            }
        }

        cout << ops.size() << '\n';
        for (const auto &op : ops) {
            cout << op[0] << ' ' << op[1] << ' ' << op[2] << '\n';
        }
    }

    return 0;
}

