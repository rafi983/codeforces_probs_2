#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    const long long INF = (1LL << 62);

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<pair<int, int>> seg(m);
        for (int i = 0; i < m; ++i) {
            cin >> seg[i].first >> seg[i].second;
        }

        sort(seg.begin(), seg.end());

        vector<long long> dp0(n + 1, INF), dp1(n + 1, INF);
        dp0[0] = 0;

        int ptr = 0;
        int pos = 1;

        while (pos <= n) {
            if (ptr < m && seg[ptr].first == pos) {
                int l = seg[ptr].first;
                int r = seg[ptr].second;
                int len = r - l + 1;

                vector<long long> ndp0(n + 1, INF), ndp1(n + 1, INF);

                for (int s = 0; s <= n; ++s) {
                    if (dp0[s] < INF) {
                        for (int x = 1; x < len; ++x) {
                            int ns = s + x;
                            long long add = 1LL * (len - x) * (s + x);
                            ndp0[ns] = min(ndp0[ns], dp0[s] + add);
                        }
                    }
                    if (dp1[s] < INF) {
                        for (int x = 1; x < len; ++x) {
                            int ns = s + x;
                            long long add = 1LL * (len - x) * (s + x);
                            ndp1[ns] = min(ndp1[ns], dp1[s] + add);
                        }
                    }
                }

                dp0.swap(ndp0);
                dp1.swap(ndp1);
                pos = r + 1;
                ++ptr;
            } else {
                vector<long long> ndp0(n + 1, INF), ndp1(n + 1, INF);

                for (int s = 0; s <= n; ++s) {
                    if (dp0[s] < INF) {
                        // Keep this free position in the "prefix" part (acts like R).
                        ndp0[s] = min(ndp0[s], dp0[s] + s);
                        // Switch here: this and all later free positions go to "suffix" (acts like L).
                        if (s + 1 <= n) {
                            ndp1[s + 1] = min(ndp1[s + 1], dp0[s]);
                        }
                    }
                    if (dp1[s] < INF) {
                        if (s + 1 <= n) {
                            ndp1[s + 1] = min(ndp1[s + 1], dp1[s]);
                        }
                    }
                }

                dp0.swap(ndp0);
                dp1.swap(ndp1);
                ++pos;
            }
        }

        long long min_bad_pairs = INF;
        for (int s = 0; s <= n; ++s) {
            min_bad_pairs = min(min_bad_pairs, dp0[s]);
            min_bad_pairs = min(min_bad_pairs, dp1[s]);
        }

        long long total_pairs = 1LL * n * (n - 1) / 2;
        long long answer = total_pairs - min_bad_pairs;
        cout << answer << '\n';
    }

    return 0;
}

