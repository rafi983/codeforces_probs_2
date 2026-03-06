#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> parent(n + 1, 0);
    vector<int> depth(n + 1, 0);
    vector<int> order;
    order.reserve(n);

    stack<int> st;
    st.push(1);
    parent[1] = -1;

    while (!st.empty()) {
        int u = st.top();
        st.pop();
        order.push_back(u);

        for (int v : graph[u]) {
            if (v == parent[u]) {
                continue;
            }
            parent[v] = u;
            depth[v] = depth[u] + 1;
            st.push(v);
        }
    }

    vector<int> maxDepthInSubtree(n + 1, 0);
    vector<int> diff(n + 2, 0);

    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        maxDepthInSubtree[u] = depth[u];
        for (int v : graph[u]) {
            if (v == parent[u]) {
                continue;
            }
            maxDepthInSubtree[u] = max(maxDepthInSubtree[u], maxDepthInSubtree[v]);
        }

        ++diff[depth[u]];
        --diff[maxDepthInSubtree[u] + 1];
    }

    int bestKept = 0;
    int current = 0;
    for (int d = 0; d <= n; ++d) {
        current += diff[d];
        bestKept = max(bestKept, current);
    }

    cout << n - bestKept << '\n';
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

