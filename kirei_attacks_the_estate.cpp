#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<long long> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }

        vector<vector<int>> g(n + 1);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<long long> mx(n + 1, 0), mn(n + 1, 0), ans(n + 1, 0);
        vector<int> parent(n + 1, 0);

        vector<int> st;
        st.reserve(n);
        st.push_back(1);
        parent[1] = -1;

        mx[1] = mn[1] = ans[1] = a[1];

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();

            for (int v : g[u]) {
                if (v == parent[u]) {
                    continue;
                }

                parent[v] = u;

                mx[v] = max(a[v], a[v] - mn[u]);
                mn[v] = min(a[v], a[v] - mx[u]);
                ans[v] = mx[v];

                st.push_back(v);
            }
        }

        for (int i = 1; i <= n; ++i) {
            cout << ans[i] << (i == n ? '\n' : ' ');
        }
    }

    return 0;
}

