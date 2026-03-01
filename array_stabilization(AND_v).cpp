#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n, d;
        cin >> n >> d;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        int g = std::gcd(n, d);
        int steps = 0;
        bool impossible = false;
        vector<char> vis(n, 0);

        for (int start = 0; start < g; ++start) {
            if (vis[start]) continue;
            vector<int> cycle;
            int cur = start;
            while (!vis[cur]) {
                vis[cur] = 1;
                cycle.push_back(a[cur]);
                cur = (cur + d) % n;
            }

            int L = (int)cycle.size();
            int ones = 0;
            for (int v : cycle) ones += v;
            if (ones == 0) continue;
            if (ones == L) {
                impossible = true;
                break;
            }

            int maxRun = 0;
            int run = 0;
            for (int v : cycle) {
                if (v == 1) {
                    ++run;
                } else {
                    maxRun = max(maxRun, run);
                    run = 0;
                }
            }
            maxRun = max(maxRun, run);

            if (cycle[0] == 1 && cycle[L - 1] == 1) {
                int prefix = 0;
                while (prefix < L && cycle[prefix] == 1) ++prefix;
                int suffix = 0;
                while (suffix < L && cycle[L - 1 - suffix] == 1) ++suffix;
                maxRun = max(maxRun, prefix + suffix);
            }

            steps = max(steps, maxRun);
        }

        if (impossible) cout << -1 << '\n';
        else cout << steps << '\n';
    }

    return 0;
}

