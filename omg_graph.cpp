#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

class DSU {
public:
    explicit DSU(int n = 0) {
        init(n);
    }

    void init(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        compMin.assign(n + 1, INF);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) return x;
        parent[x] = find(parent[x]);
        return parent[x];
    }

    void add_edge(int u, int v, int w) {
        int ru = find(u);
        int rv = find(v);

        if (ru == rv) {
            compMin[ru] = min(compMin[ru], w);
            return;
        }

        if (sz[ru] < sz[rv]) {
            swap(ru, rv);
        }

        parent[rv] = ru;
        sz[ru] += sz[rv];
        compMin[ru] = min(compMin[ru], compMin[rv]);
        compMin[ru] = min(compMin[ru], w);
    }

    int component_min(int x) {
        return compMin[find(x)];
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

private:
    static constexpr int INF = numeric_limits<int>::max();
    vector<int> parent;
    vector<int> sz;
    vector<int> compMin;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<Edge> edges(m);
        for (int i = 0; i < m; ++i) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }

        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.w < b.w;
        });

        DSU dsu(n);
        long long ans = (1LL << 62);

        for (const Edge& e : edges) {
            dsu.add_edge(e.u, e.v, e.w);
            if (dsu.same(1, n)) {
                long long mn = dsu.component_min(1);
                ans = min(ans, mn + e.w);
            }
        }

        cout << ans << '\n';
    }

    return 0;
}

