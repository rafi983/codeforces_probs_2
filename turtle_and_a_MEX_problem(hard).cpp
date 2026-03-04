#include <bits/stdc++.h>
using namespace std;

static long long sum_upto(long long x) {
    return x * (x + 1) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        long long m;
        cin >> n >> m;

        vector<pair<int, int>> edges;
        edges.reserve(n);
        int max_second_mex = 0;
        int max_first_mex = 0;

        for (int i = 0; i < n; ++i) {
            int l;
            cin >> l;

            vector<char> seen(l + 2, 0);
            for (int j = 0; j < l; ++j) {
                long long x;
                cin >> x;
                if (0 <= x && x <= l + 1) {
                    seen[static_cast<int>(x)] = 1;
                }
            }

            int first_mex = 0;
            while (first_mex <= l + 1 && seen[first_mex]) {
                ++first_mex;
            }

            int second_mex = first_mex + 1;
            while (second_mex <= l + 1 && seen[second_mex]) {
                ++second_mex;
            }

            edges.push_back({first_mex, second_mex});
            max_second_mex = max(max_second_mex, second_mex);
            max_first_mex = max(max_first_mex, first_mex);
        }

        int U = max_second_mex;
        vector<vector<int>> out(U + 1);
        vector<int> cnt(U + 1, 0);

        for (const auto &e : edges) {
            int a = e.first;
            int b = e.second;
            out[a].push_back(b);
            ++cnt[a];
        }

        vector<int> dp(U + 1, 0);
        for (int v = U; v >= 0; --v) {
            int best = v;
            for (int to : out[v]) {
                best = max(best, dp[to]);
            }
            dp[v] = best;
        }

        int global_boost = 0;
        for (int v = 0; v <= U; ++v) {
            if (cnt[v] >= 2) {
                global_boost = max(global_boost, dp[v]);
            }
        }

        long long upto = min<long long>(m, U);
        long long ans = 0;

        for (long long k = 0; k <= upto; ++k) {
            ans += max<long long>({dp[static_cast<int>(k)], global_boost, max_first_mex});
        }

        if (m > U) {
            ans += sum_upto(m) - sum_upto(U);
        }

        cout << ans << '\n';
    }

    return 0;
}
