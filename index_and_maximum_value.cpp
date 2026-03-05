#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        long long mx = LLONG_MIN;
        for (int i = 0; i < n; ++i) {
            long long x;
            cin >> x;
            mx = max(mx, x);
        }

        for (int i = 0; i < m; ++i) {
            char c;
            long long l, r;
            cin >> c >> l >> r;

            if (l <= mx && mx <= r) {
                if (c == '+') {
                    ++mx;
                } else {
                    --mx;
                }
            }

            cout << mx << (i + 1 == m ? '\n' : ' ');
        }
    }

    return 0;
}

