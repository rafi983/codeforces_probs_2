#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> a(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];

        vector<int> next_leq(n + 2, n + 1);
        vector<pair<long long, int>> st;
        st.reserve(n);
        for (int i = n; i >= 1; --i) {
            while (!st.empty() && st.back().first > a[i]) st.pop_back();
            next_leq[i] = st.empty() ? n + 1 : st.back().second;
            st.push_back({a[i], i});
        }

        vector<int> next_jump(n + 2, n + 1);
        for (int i = n - 1; i >= 1; --i) {
            if (a[i + 1] > a[i] + 1) next_jump[i] = i + 1; else next_jump[i] = next_jump[i + 1];
        }

        vector<int> cut(n + 2, n + 1);
        for (int i = 1; i <= n; ++i) cut[i] = min(next_leq[i], next_jump[i]);

        vector<long long> dp(n + 2, 0);
        for (int i = n; i >= 1; --i) dp[i] = (long long)(n - i + 1) + dp[cut[i]];

        long long ans = 0;
        for (int i = 1; i <= n; ++i) ans += dp[i];
        cout << ans;
        if (T) cout << '\n';
    }
    return 0;
}

