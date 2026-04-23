#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        string top, bottom;
        cin >> n >> top >> bottom;

        const long long INF = (long long)4e18;
        vector<long long> dp(n + 1, INF);
        dp[0] = 0;

        for (int i = 1; i <= n; ++i) {
            int costVertical = (top[i - 1] == bottom[i - 1] ? 0 : 1);
            dp[i] = min(dp[i], dp[i - 1] + costVertical);

            if (i >= 2) {
                int costTop = (top[i - 2] == top[i - 1] ? 0 : 1);
                int costBottom = (bottom[i - 2] == bottom[i - 1] ? 0 : 1);
                dp[i] = min(dp[i], dp[i - 2] + costTop + costBottom);
            }
        }

        cout << dp[n] << '\n';
    }

    return 0;
}

