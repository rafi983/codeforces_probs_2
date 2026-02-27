#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        vector<int> left_child(n, -1), right_child(n, -1), parent(n, -1);
        vector<int> st;
        st.reserve(n);
        for (int i = 0; i < n; ++i) {
            int last = -1;
            while (!st.empty() && a[st.back()] < a[i]) {
                last = st.back();
                st.pop_back();
            }
            if (!st.empty()) {
                parent[i] = st.back();
                right_child[st.back()] = i;
            }
            if (last != -1) {
                parent[last] = i;
                left_child[i] = last;
            }
            st.push_back(i);
        }

        int root = 0;
        for (int i = 0; i < n; ++i) {
            if (parent[i] == -1) {
                root = i;
                break;
            }
        }

        vector<int> order;
        order.reserve(n);
        vector<int> stack_nodes;
        stack_nodes.push_back(root);
        while (!stack_nodes.empty()) {
            int v = stack_nodes.back();
            stack_nodes.pop_back();
            order.push_back(v);
            if (left_child[v] != -1) stack_nodes.push_back(left_child[v]);
            if (right_child[v] != -1) stack_nodes.push_back(right_child[v]);
        }

        vector<int> sz(n, 0), dp(n, 0);
        for (int idx = (int)order.size() - 1; idx >= 0; --idx) {
            int v = order[idx];
            int l = left_child[v];
            int r = right_child[v];
            int sz_l = (l == -1) ? 0 : sz[l];
            int sz_r = (r == -1) ? 0 : sz[r];
            int dp_l = (l == -1) ? 0 : dp[l];
            int dp_r = (r == -1) ? 0 : dp[r];

            sz[v] = 1 + sz_l + sz_r;
            dp[v] = min(sz_l + dp_r, sz_r + dp_l);
        }

        cout << dp[root] << '\n';
    }

    return 0;
}

