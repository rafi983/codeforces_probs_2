#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct AdjEdge {
    int to;
    int id;
};

struct DirEdge {
    int from;
    int to;
    long long val;
    int rev;
};

static const int NEG_INF = -1000000000;

static pair<int, vector<int>> bfs_far(int start, const vector<vector<int>> &g) {
    int n = (int)g.size() - 1;
    vector<int> dist(n + 1, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    int far = start;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (dist[v] > dist[far]) far = v;
        for (int to : g[v]) {
            if (dist[to] == -1) {
                dist[to] = dist[v] + 1;
                q.push(to);
            }
        }
    }
    return {far, dist};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<long long> a(n + 1);
        long long total_sum = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            total_sum += a[i];
        }

        vector<pair<int, int>> und(n);
        vector<vector<AdjEdge>> adj(n + 1);
        vector<vector<int>> g(n + 1);
        for (int i = 1; i <= n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            und[i] = {u, v};
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
            g[u].push_back(v);
            g[v].push_back(u);
        }

        auto p1 = bfs_far(1, g);
        auto p2 = bfs_far(p1.first, g);
        int diameter = 0;
        for (int i = 1; i <= n; ++i) diameter = max(diameter, p2.second[i]);
        if (k > diameter) {
            cout << -1 << '\n';
            continue;
        }

        vector<int> parent(n + 1, 0), parent_edge(n + 1, 0), order;
        order.reserve(n);
        vector<int> st;
        st.push_back(1);
        parent[1] = -1;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            order.push_back(v);
            for (auto e : adj[v]) {
                if (e.to == parent[v]) continue;
                parent[e.to] = v;
                parent_edge[e.to] = e.id;
                st.push_back(e.to);
            }
        }

        vector<long long> sub(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            int v = order[i];
            long long s = a[v];
            for (auto e : adj[v]) {
                if (e.to == parent[v]) continue;
                s += sub[e.to];
            }
            sub[v] = s;
        }

        int m = 2 * (n - 1);
        vector<DirEdge> d(m);
        vector<int> id_uv(n, -1), id_vu(n, -1);
        int ptr = 0;
        for (int i = 1; i <= n - 1; ++i) {
            int u = und[i].first;
            int v = und[i].second;

            long long u_to_v, v_to_u;
            if (parent[v] == u) {
                u_to_v = sub[v];
                v_to_u = total_sum - sub[v];
            } else {
                u_to_v = total_sum - sub[u];
                v_to_u = sub[u];
            }

            int a_id = ptr++;
            int b_id = ptr++;
            d[a_id] = {u, v, u_to_v, b_id};
            d[b_id] = {v, u, v_to_u, a_id};

            id_uv[i] = a_id;
            id_vu[i] = b_id;
        }

        vector<vector<int>> out(n + 1);
        for (int i = 0; i < m; ++i) out[d[i].from].push_back(i);
        for (int v = 1; v <= n; ++v) {
            sort(out[v].begin(), out[v].end(), [&](int i, int j) {
                return d[i].val < d[j].val;
            });
        }

        vector<int> all_idx(m);
        for (int i = 0; i < m; ++i) all_idx[i] = i;
        sort(all_idx.begin(), all_idx.end(), [&](int i, int j) {
            return d[i].val < d[j].val;
        });

        auto can = [&](long long X) -> bool {
            vector<int> dp(m, NEG_INF);

            vector<int> p(n + 1, 0);
            vector<int> best1_id(n + 1, -1), best2_id(n + 1, -1);
            vector<int> best1_val(n + 1, NEG_INF), best2_val(n + 1, NEG_INF);

            auto add_candidate = [&](int node, int edge_id) {
                int val = dp[edge_id];
                if (val > best1_val[node]) {
                    best2_val[node] = best1_val[node];
                    best2_id[node] = best1_id[node];
                    best1_val[node] = val;
                    best1_id[node] = edge_id;
                } else if (val > best2_val[node]) {
                    best2_val[node] = val;
                    best2_id[node] = edge_id;
                }
            };

            for (int idx : all_idx) {
                const DirEdge &cur = d[idx];

                if (cur.val < X) {
                    dp[idx] = NEG_INF;
                    continue;
                }

                long long lim = cur.val - X;
                int node = cur.to;
                while (p[node] < (int)out[node].size() && d[out[node][p[node]]].val <= lim) {
                    int e_id = out[node][p[node]];
                    if (dp[e_id] > NEG_INF / 2) add_candidate(node, e_id);
                    ++p[node];
                }

                int best = best1_val[node];
                if (best1_id[node] == cur.rev) best = best2_val[node];
                if (best < 0) best = 0;

                dp[idx] = 1 + best;
                if (cur.val <= total_sum - X && dp[idx] >= k) return true;
            }

            return false;
        };

        long long lo = 1, hi = total_sum / (k + 1), ans = 1;
        while (lo <= hi) {
            long long mid = (lo + hi) >> 1;
            if (can(mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
