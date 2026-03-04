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

        if (n % 2 == 0) {
            cout << -1 << '\n';
            continue;
        }

        vector<int> pos;
        pos.reserve(n);

        int l = 1, r = n;
        while (l <= r) {
            pos.push_back(r--);
            if (l <= r) pos.push_back(l++);
        }

        vector<int> p(n + 1);
        for (int k = 1; k <= n; ++k) {
            p[pos[k - 1]] = k;
        }

        for (int i = 1; i <= n; ++i) {
            if (i > 1) cout << ' ';
            cout << p[i];
        }
        cout << '\n';
    }

    return 0;
}

