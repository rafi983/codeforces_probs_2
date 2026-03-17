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

        vector<string> s(n);
        for (int i = 0; i < n; ++i) {
            cin >> s[i];
        }

        bool ok = true;

        for (int i = 0; i < n; ++i) {
            if (s[i][i] != '1') ok = false;
        }

        for (int i = 0; i < n && ok; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (s[i][j] == '1' && s[j][i] == '1') {
                    ok = false;
                    break;
                }
            }
        }

        for (int i = 0; i < n && ok; ++i) {
            for (int j = 0; j < n && ok; ++j) {
                if (s[i][j] != '1') continue;
                for (int k = 0; k < n; ++k) {
                    if (s[j][k] == '1' && s[i][k] != '1') {
                        ok = false;
                        break;
                    }
                }
            }
        }

        vector<pair<int, int>> edges;

        if (ok) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (i == j || s[i][j] != '1') continue;

                    bool hasMiddle = false;
                    for (int k = 0; k < n; ++k) {
                        if (k == i || k == j) continue;
                        if (s[i][k] == '1' && s[k][j] == '1') {
                            hasMiddle = true;
                            break;
                        }
                    }

                    if (!hasMiddle) {
                        edges.push_back({i, j});
                    }
                }
            }

            if ((int)edges.size() != n - 1) {
                ok = false;
            }
        }

        if (ok) {
            vector<vector<int>> und(n);
            vector<vector<int>> g(n);
            for (auto [u, v] : edges) {
                g[u].push_back(v);
                und[u].push_back(v);
                und[v].push_back(u);
            }

            vector<int> vis(n, 0);
            queue<int> q;
            q.push(0);
            vis[0] = 1;
            int seen = 1;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : und[u]) {
                    if (!vis[v]) {
                        vis[v] = 1;
                        ++seen;
                        q.push(v);
                    }
                }
            }

            if (seen != n) {
                ok = false;
            }

            if (ok) {
                vector<string> got(n, string(n, '0'));
                for (int src = 0; src < n; ++src) {
                    vector<int> dvis(n, 0);
                    stack<int> st;
                    st.push(src);
                    dvis[src] = 1;

                    while (!st.empty()) {
                        int u = st.top();
                        st.pop();
                        for (int v : g[u]) {
                            if (!dvis[v]) {
                                dvis[v] = 1;
                                st.push(v);
                            }
                        }
                    }

                    for (int v = 0; v < n; ++v) {
                        if (dvis[v]) got[src][v] = '1';
                    }
                }

                if (got != s) {
                    ok = false;
                }
            }
        }

        if (!ok) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
            for (auto [u, v] : edges) {
                cout << (u + 1) << ' ' << (v + 1) << '\n';
            }
        }
    }

    return 0;
}

