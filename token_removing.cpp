#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        int64 mod;
        cin >> n >> mod;

        vector<int64> dp(n + 1, 0);
        dp[0] = 1 % mod;

        for (int j = n; j >= 1; --j) {
            int maxChosenLarger = n - j;
            for (int c = maxChosenLarger; c >= 0; --c) {
                int64 ways = (int64)j * (n - j + 1 - c);
                dp[c + 1] = (dp[c + 1] + dp[c] * ways) % mod;
            }
        }

        int64 ans = 0;
        for (int c = 0; c <= n; ++c) {
            ans += dp[c];
            if (ans >= mod) ans -= mod;
        }

        cout << ans % mod << '\n';
    }

    return 0;
}

