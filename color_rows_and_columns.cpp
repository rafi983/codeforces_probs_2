#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    const long long INF = (long long)4e18;
    vector<long long> dp(k + 1, INF);
    dp[0] = 0;

    int total_possible = 0;

    for (int rect = 0; rect < n; ++rect) {
        int a, b;
        cin >> a >> b;

        total_possible += a + b;

        vector<long long> best(k + 1, INF);
        best[0] = 0;

        for (int rows = 0; rows <= b && rows <= k; ++rows) {
            for (int cols = 0; cols <= a && rows + cols <= k; ++cols) {
                int gain = rows + cols;
                long long cost = 1LL * rows * a + 1LL * cols * b - 1LL * rows * cols;
                best[gain] = min(best[gain], cost);
            }
        }

        vector<long long> next(k + 1, INF);
        for (int have = 0; have <= k; ++have) {
            if (dp[have] == INF) {
                continue;
            }
            for (int gain = 0; have + gain <= k; ++gain) {
                if (best[gain] == INF) {
                    continue;
                }
                next[have + gain] = min(next[have + gain], dp[have] + best[gain]);
            }
        }
        dp.swap(next);
    }

    if (total_possible < k || dp[k] == INF) {
        cout << -1 << '\n';
    } else {
        cout << dp[k] << '\n';
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

