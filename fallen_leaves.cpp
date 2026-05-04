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

        vector<vector<int>> g(n + 1);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<int> is_leaf(n + 1, 0);
        int leaf_count = 0;
        for (int u = 1; u <= n; ++u) {
            if ((int)g[u].size() <= 1) {
                is_leaf[u] = 1;
                ++leaf_count;
            }
        }

        vector<int> parent(n + 1, 0), order;
        order.reserve(n);

        stack<int> st;
        st.push(1);
        parent[1] = -1;
        while (!st.empty()) {
            int u = st.top();
            st.pop();
            order.push_back(u);
            for (int v : g[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                st.push(v);
            }
        }

        vector<int> sub_leaves(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];
            int cnt = is_leaf[u];
            for (int v : g[u]) {
                if (v == parent[u]) continue;
                cnt += sub_leaves[v];
            }
            sub_leaves[u] = cnt;
        }

        long long base = 0;
        vector<int> delta_to_parent(n + 1, 0);
        for (int v = 2; v <= n; ++v) {
            int w = sub_leaves[v] & 1;
            base += w;
            delta_to_parent[v] = 1 - 2 * w;
        }

        if ((leaf_count & 1) == 0) {
            cout << base << '\n';
            continue;
        }

        vector<long long> pref_delta(n + 1, 0);
        for (int u : order) {
            for (int v : g[u]) {
                if (v == parent[u]) continue;
                pref_delta[v] = pref_delta[u] + delta_to_parent[v];
            }
        }

        long long answer = (long long)4e18;
        for (int u = 1; u <= n; ++u) {
            if (is_leaf[u]) {
                answer = min(answer, base + pref_delta[u]);
            }
        }

        cout << answer << '\n';
    }

    return 0;
}
