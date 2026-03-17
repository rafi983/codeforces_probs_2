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

        vector<vector<int>> g(n + 1);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<int> color(n + 1, -1);
        long long answer = 0;

        for (int s = 1; s <= n; ++s) {
            if (color[s] != -1) continue;

            queue<int> q;
            q.push(s);
            color[s] = 0;

            long long cnt[2] = {1, 0};
            bool bip = true;

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : g[u]) {
                    if (color[v] == -1) {
                        color[v] = color[u] ^ 1;
                        ++cnt[color[v]];
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        bip = false;
                    }
                }
            }

            if (bip) {
                answer += max(cnt[0], cnt[1]);
            }
        }

        cout << answer << '\n';
    }

    return 0;
}

