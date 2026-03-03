#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;

        vector<long long> a(n), b(m);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < m; ++i) cin >> b[i];

        string s;
        cin >> s;

        sort(b.begin(), b.end());

        const int INF = k + 5;
        vector<int> firstPos(k + 1, INF), firstNeg(k + 1, INF);

        int cur = 0, mx = 0, mn = 0;
        for (int i = 1; i <= k; ++i) {
            cur += (s[i - 1] == 'R' ? 1 : -1);

            if (cur > mx) {
                for (int d = mx + 1; d <= cur; ++d) {
                    firstPos[d] = i;
                }
                mx = cur;
            }
            if (cur < mn) {
                for (int d = -mn + 1; d <= -cur; ++d) {
                    firstNeg[d] = i;
                }
                mn = cur;
            }
        }

        vector<int> deathsAt(k + 1, 0);

        for (long long x : a) {
            int death = INF;
            auto it = lower_bound(b.begin(), b.end(), x);

            if (it != b.end()) {
                long long dr = *it - x;
                if (dr >= 1 && dr <= k) {
                    death = min(death, firstPos[(int)dr]);
                }
            }

            if (it != b.begin()) {
                auto lit = prev(it);
                long long dl = x - *lit;
                if (dl >= 1 && dl <= k) {
                    death = min(death, firstNeg[(int)dl]);
                }
            }

            if (death <= k) {
                ++deathsAt[death];
            }
        }

        int dead = 0;
        for (int i = 1; i <= k; ++i) {
            dead += deathsAt[i];
            cout << (n - dead) << (i == k ? '\n' : ' ');
        }
    }

    return 0;
}

