#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

static const int INF = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, m, l;
        cin >> n >> m >> l;

        long long total = 0;
        int min_odd = INF;
        bool has_odd = false;

        for (int i = 0; i < l; ++i) {
            int x;
            cin >> x;
            total += x;
            if (x & 1) {
                has_odd = true;
                if (x < min_odd) min_odd = x;
            }
        }

        vector<vector<int>> g(n + 1);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        // Maximum subset-sum with given parity.
        long long max_par[2] = {-1, -1};
        int p = static_cast<int>(total & 1LL);
        max_par[p] = total;
        if (has_odd) {
            max_par[p ^ 1] = total - min_odd;
        }

        vector<vector<int>> dist(n + 1, vector<int>(2, INF));
        queue<pair<int, int>> q;
        dist[1][0] = 0;
        q.push({1, 0});

        while (!q.empty()) {
            auto [u, par] = q.front();
            q.pop();

            for (int v : g[u]) {
                int np = par ^ 1;
                if (dist[v][np] > dist[u][par] + 1) {
                    dist[v][np] = dist[u][par] + 1;
                    q.push({v, np});
                }
            }
        }

        string ans(n, '0');
        for (int v = 1; v <= n; ++v) {
            bool ok = false;
            if (max_par[0] >= 0 && dist[v][0] != INF && dist[v][0] <= max_par[0]) ok = true;
            if (max_par[1] >= 0 && dist[v][1] != INF && dist[v][1] <= max_par[1]) ok = true;
            if (ok) ans[v - 1] = '1';
        }

        cout << ans << '\n';
    }

    return 0;
}
