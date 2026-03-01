#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        vector<long long> b = a;
        sort(b.begin(), b.end());

        struct Op { int l, r, d; };
        vector<Op> ops;

        for (int i = 0; i < n; ++i) {
            if (a[i] == b[i]) continue;
            int j = i + 1;
            while (j < n && a[j] != b[i]) ++j;
            if (j == n) continue; // should not happen since b is sorted version of a
            int l = i + 1;
            int r = j + 1;
            int d = r - l;
            long long val = a[j];
            for (int k = j; k > i; --k) {
                a[k] = a[k - 1];
            }
            a[i] = val;
            ops.push_back({l, r, d});
        }

        cout << ops.size() << '\n';
        for (auto &op : ops) {
            cout << op.l << ' ' << op.r << ' ' << op.d << '\n';
        }
    }

    return 0;
}
