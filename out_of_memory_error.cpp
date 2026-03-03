#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        long long h;
        cin >> n >> m >> h;

        vector<long long> base(n), cap(n);
        for (int i = 0; i < n; ++i) {
            cin >> base[i];
            cap[i] = h - base[i];
        }

        vector<long long> add(n, 0);
        vector<int> seen(n, 0);
        int epoch = 1;

        for (int op = 0; op < m; ++op) {
            int b;
            long long c;
            cin >> b >> c;
            --b;

            if (seen[b] != epoch) {
                seen[b] = epoch;
                add[b] = 0;
            }

            add[b] += c;

            if (add[b] > cap[b]) {
                ++epoch;
            }
        }

        for (int i = 0; i < n; ++i) {
            long long inc = (seen[i] == epoch ? add[i] : 0LL);
            cout << (base[i] + inc) << (i + 1 == n ? '\n' : ' ');
        }
    }

    return 0;
}

