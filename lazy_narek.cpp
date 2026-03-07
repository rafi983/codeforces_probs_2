#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    const string pat = "narek";
    array<bool, 26> relevant{};
    for (char c : pat) {
        relevant[c - 'a'] = true;
    }

    const long long NEG = -(1LL << 60);
    array<long long, 5> dp;
    dp.fill(NEG);
    dp[0] = 0;

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;

        array<long long, 5> ndp = dp;

        for (int start = 0; start < 5; ++start) {
            if (dp[start] == NEG) continue;

            int state = start;
            long long delta = 0;

            for (char c : s) {
                if (c == pat[state]) {
                    ++delta;
                    state = (state + 1) % 5;
                } else if (relevant[c - 'a']) {
                    --delta;
                }
            }

            ndp[state] = max(ndp[state], dp[start] + delta);
        }

        dp = ndp;
    }

    long long ans = 0;
    for (int state = 0; state < 5; ++state) {
        ans = max(ans, dp[state] - 2LL * state);
    }

    cout << ans << '\n';
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

