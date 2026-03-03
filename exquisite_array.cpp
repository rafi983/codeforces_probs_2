#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class DSU {
public:
    DSU() : total(0) {}

    explicit DSU(int n) {
        init(n);
    }

    void init(int n) {
        parent.resize(n);
        sz.assign(n, 1);
        active.assign(n, 0);
        for (int i = 0; i < n; ++i) parent[i] = i;
        total = 0;
    }

    void activate(int v) {
        active[v] = 1;
        total += 1;
    }

    bool is_active(int v) const {
        return active[v] != 0;
    }

    long long get_total() const {
        return total;
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;

        if (sz[a] < sz[b]) {
            int tmp = a;
            a = b;
            b = tmp;
        }

        total -= contribution(sz[a]);
        total -= contribution(sz[b]);

        parent[b] = a;
        sz[a] += sz[b];

        total += contribution(sz[a]);
    }

private:
    vector<int> parent;
    vector<int> sz;
    vector<char> active;
    long long total;

    static long long contribution(long long len) {
        return len * (len + 1) / 2;
    }

    int find(int v) {
        if (parent[v] == v) return v;
        parent[v] = find(parent[v]);
        return parent[v];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i];
        }

        int m = n - 1;
        vector<vector<int>> by_diff(n);
        for (int i = 0; i < m; ++i) {
            int diff = abs(p[i] - p[i + 1]);
            by_diff[diff].push_back(i);
        }

        DSU dsu(m);
        vector<long long> ans(n, 0);

        for (int k = n - 1; k >= 1; --k) {
            for (int pos : by_diff[k]) {
                dsu.activate(pos);

                if (pos - 1 >= 0 && dsu.is_active(pos - 1)) {
                    dsu.unite(pos, pos - 1);
                }
                if (pos + 1 < m && dsu.is_active(pos + 1)) {
                    dsu.unite(pos, pos + 1);
                }
            }

            ans[k] = dsu.get_total();
        }

        for (int k = 1; k <= n - 1; ++k) {
            cout << ans[k] << (k == n - 1 ? '\n' : ' ');
        }
    }

    return 0;
}

