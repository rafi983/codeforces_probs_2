#include <iostream>
#include <vector>

using namespace std;

static const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXN = 200000;
    vector<int> pow2(MAXN + 1, 1);
    for (int i = 1; i <= MAXN; ++i) {
        pow2[i] = (pow2[i - 1] * 2LL) % MOD;
    }

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
        vector<vector<int>> children(n + 1);
        vector<int> st;
        st.push_back(1);
        parent[1] = -1;

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            for (int v : g[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                children[u].push_back(v);
                st.push_back(v);
            }
        }

        int leaf_cnt = 0;
        for (int u = 1; u <= n; ++u) {
            if (children[u].empty()) {
                ++leaf_cnt;
            }
        }

        if (leaf_cnt >= 3) {
            cout << 0 << '\n';
            continue;
        }

        if (leaf_cnt == 1) {
            cout << pow2[n] << '\n';
            continue;
        }

        int split = -1;
        for (int u = 1; u <= n; ++u) {
            if (children[u].size() == 2) {
                split = u;
                break;
            }
        }

        int c1 = children[split][0];
        int c2 = children[split][1];

        auto chain_len = [&](int start) {
            int len = 1;
            int u = start;
            while (children[u].size() == 1) {
                u = children[u][0];
                ++len;
            }
            return len;
        };

        int p = chain_len(c1);
        int q = chain_len(c2);

        int rest = n - (p + q);
        int d = p - q;
        if (d < 0) d = -d;

        int branch_ways;
        if (d == 0) {
            branch_ways = 2;
        } else {
            branch_ways = (3LL * pow2[d - 1]) % MOD;
        }

        int ans = (pow2[rest] * 1LL * branch_ways) % MOD;
        cout << ans << '\n';
    }

    return 0;
}

