#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n;
    int m, q;
    cin >> n >> m >> q;

    vector<long long> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    sort(b.begin(), b.end());

    for (int i = 0; i < q; ++i) {
        long long a;
        cin >> a;

        auto it = lower_bound(b.begin(), b.end(), a);

        if (it == b.begin()) {
            cout << b.front() - 1 << '\n';
        } else if (it == b.end()) {
            cout << n - b.back() << '\n';
        } else {
            long long right = *it;
            long long left = *prev(it);
            cout << (right - left) / 2 << '\n';
        }
    }
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

