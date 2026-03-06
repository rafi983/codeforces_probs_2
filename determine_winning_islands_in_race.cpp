#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> alt(n + 1);
        vector<pair<int, int>> edges;
        edges.reserve(m);

        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            alt[u].push_back(v);
            edges.push_back({u, v});
        }

        const int INF = (int)1e9;
        vector<int> dist(n + 1, INF);
        dist[1] = 0;

        for (int u = 1; u <= n; ++u) {
            if (u < n) {
                dist[u + 1] = min(dist[u + 1], dist[u] + 1);
            }
            for (int v : alt[u]) {
                dist[v] = min(dist[v], dist[u] + 1);
            }
        }

        vector<int> diff(n + 2, 0);
        for (auto [u, v] : edges) {
            int l = u + 1;
            int r = v - dist[u] - 2;
            if (l <= r) {
                r = min(r, n - 1);
                diff[l]++;
                diff[r + 1]--;
            }
        }

        string ans(n - 1, '1');
        int cover = 0;
        for (int s = 2; s <= n - 1; ++s) {
            cover += diff[s];
            if (cover > 0) {
                ans[s - 1] = '0';
            }
        }

        cout << ans << '\n';
    }

    return 0;
}

