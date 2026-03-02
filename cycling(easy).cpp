#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) {
        return 0;
    }
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }

        const long long INF = (1LL << 62);
        vector<long long> dp(n + 1, INF), nextdp(n + 1, INF), suffixMin(n + 2, INF);

        for (int j = 1; j <= n; ++j) {
            dp[j] = (long long)(n - j) + a[j];
        }

        for (int i = n - 1; i >= 1; --i) {
            suffixMin[n + 1] = INF;
            for (int j = n; j >= 1; --j) {
                suffixMin[j] = min(dp[j], suffixMin[j + 1]);
            }

            fill(nextdp.begin(), nextdp.end(), INF);

            for (int j = 1; j <= n; ++j) {
                if (dp[j] < INF) {
                    nextdp[j] = min(nextdp[j], dp[j] + 1 + a[j]);
                }
            }

            for (int k = 1; k <= i; ++k) {
                long long bestGreater = suffixMin[k + 1];
                if (bestGreater < INF) {
                    long long cand = bestGreater + (long long)(i - k) + a[k];
                    if (cand < nextdp[k]) {
                        nextdp[k] = cand;
                    }
                }
            }

            dp.swap(nextdp);
        }

        long long ans = INF;
        for (int j = 1; j <= n; ++j) {
            ans = min(ans, dp[j]);
        }
        cout << ans << "\n";
    }

    return 0;
}
