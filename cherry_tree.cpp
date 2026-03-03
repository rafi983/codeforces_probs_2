#include <array>
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

        vector<vector<int>> g(n + 1);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<int> parent(n + 1, 0);
        vector<int> order;
        order.reserve(n);

        vector<int> st;
        st.push_back(1);
        parent[1] = -1;

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            order.push_back(u);

            for (int v : g[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                st.push_back(v);
            }
        }

        vector<vector<int>> children(n + 1);
        for (int v = 2; v <= n; ++v) {
            children[parent[v]].push_back(v);
        }

        vector<array<char, 3>> can(n + 1);

        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];

            if (children[u].empty()) {
                can[u] = {0, 1, 0};
                continue;
            }

            array<char, 3> combine = {1, 0, 0};
            for (int v : children[u]) {
                array<char, 3> next = {0, 0, 0};
                for (int a = 0; a < 3; ++a) {
                    if (!combine[a]) continue;
                    for (int b = 0; b < 3; ++b) {
                        if (!can[v][b]) continue;
                        next[(a + b) % 3] = 1;
                    }
                }
                combine = next;
            }

            can[u] = combine;
            can[u][1] = 1;
        }

        cout << (can[1][0] ? "YES" : "NO") << '\n';
    }

    return 0;
}

