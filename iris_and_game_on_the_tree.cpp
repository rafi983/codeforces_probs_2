#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> deg(n + 1, 0);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            ++deg[u];
            ++deg[v];
        }

        string s;
        cin >> s;
        s = " " + s;  // 1-indexed access

        long long leaf0 = 0, leaf1 = 0, leafQ = 0;
        for (int v = 2; v <= n; ++v) {
            if (deg[v] == 1) {
                if (s[v] == '0') {
                    ++leaf0;
                } else if (s[v] == '1') {
                    ++leaf1;
                } else {
                    ++leafQ;
                }
            }
        }

        long long totalQ = 0;
        for (int v = 1; v <= n; ++v) {
            if (s[v] == '?') {
                ++totalQ;
            }
        }

        long long internalQ = totalQ - leafQ - (s[1] == '?' ? 1LL : 0LL);
        long long ans = 0;

        if (s[1] == '0') {
            ans = leaf1 + (leafQ + 1) / 2;
        } else if (s[1] == '1') {
            ans = leaf0 + (leafQ + 1) / 2;
        } else {
            if (leaf0 == leaf1) {
                ans = leaf0 + (leafQ + (internalQ & 1LL)) / 2;
            } else {
                ans = max(leaf0, leaf1) + leafQ / 2;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}

