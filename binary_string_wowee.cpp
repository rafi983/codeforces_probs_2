#include <iostream>
#include <string>
#include <vector>

using namespace std;

static const int MOD = 998244353;
static const int MAXN = 500;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> C(MAXN + 1, vector<int>(MAXN + 1, 0));
    for (int n = 0; n <= MAXN; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int r = 1; r < n; ++r) {
            C[n][r] = C[n - 1][r - 1] + C[n - 1][r];
            if (C[n][r] >= MOD) C[n][r] -= MOD;
        }
    }

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;

        vector<int> dp(k + 1, 0), ndp(k + 1, 0);
        dp[0] = 1;

        for (int idx = n - 1; idx >= 0; --idx) {
            fill(ndp.begin(), ndp.end(), 0);

            int bit = s[idx] - '0';
            for (int total_len = 0; total_len <= k; ++total_len) {
                long long ways = 0;

                for (int c = 0; c <= total_len; ++c) {
                    int prev_len = total_len - c;
                    if (dp[prev_len] == 0) continue;

                    int available;
                    if (bit == 0) {
                        available = (total_len + 1) / 2;
                    } else {
                        available = total_len / 2;
                    }

                    if (c > available) continue;

                    ways += 1LL * dp[prev_len] * C[available][c] % MOD;
                    if (ways >= (1LL << 62)) ways %= MOD;
                }

                ndp[total_len] = static_cast<int>(ways % MOD);
            }

            dp.swap(ndp);
        }

        cout << dp[k] << '\n';
    }

    return 0;
}

