#include <bits/stdc++.h>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> sz;
    vector<int> leftBound;
    vector<array<int, 2>> maxParityCount;
    long long totalIndependent = 0;
    int goodComponents = 0;

    explicit DSU(int n)
        : parent(n + 1), sz(n + 1, 0), leftBound(n + 1, 0), maxParityCount(n + 1, {0, 0}) {
    }

    static long long independent_size(int len) {
        return (len + 1) / 2;
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    bool is_good_root(int root) const {
        int totalMax = maxParityCount[root][0] + maxParityCount[root][1];
        if (totalMax == 0) {
            return false;
        }
        if (sz[root] % 2 == 0) {
            return true;
        }
        return maxParityCount[root][leftBound[root] & 1] > 0;
    }

    void remove_root_contribution(int root) {
        totalIndependent -= independent_size(sz[root]);
        if (is_good_root(root)) {
            --goodComponents;
        }
    }

    void add_root_contribution(int root) {
        totalIndependent += independent_size(sz[root]);
        if (is_good_root(root)) {
            ++goodComponents;
        }
    }

    void activate(int pos, bool isGlobalMaximum) {
        parent[pos] = pos;
        sz[pos] = 1;
        leftBound[pos] = pos;
        maxParityCount[pos] = {0, 0};
        if (isGlobalMaximum) {
            ++maxParityCount[pos][pos & 1];
        }
        add_root_contribution(pos);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }

        remove_root_contribution(a);
        remove_root_contribution(b);

        if (sz[a] < sz[b]) {
            swap(a, b);
        }

        parent[b] = a;
        sz[a] += sz[b];
        leftBound[a] = min(leftBound[a], leftBound[b]);
        maxParityCount[a][0] += maxParityCount[b][0];
        maxParityCount[a][1] += maxParityCount[b][1];

        add_root_contribution(a);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 0;
    cin >> t;
    while (t--) {
        int n = 0;
        cin >> n;

        vector<long long> a(n + 1);
        long long globalMax = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            globalMax = max(globalMax, a[i]);
        }

        vector<pair<long long, int>> order;
        order.reserve(n);
        for (int i = 1; i <= n; ++i) {
            order.push_back({a[i], i});
        }
        sort(order.begin(), order.end(), greater<pair<long long, int>>());

        DSU dsu(n);
        vector<char> active(n + 2, 0);
        long long answer = 0;

        for (int i = 0; i < n;) {
            int j = i;
            long long value = order[i].first;
            while (j < n && order[j].first == value) {
                int pos = order[j].second;
                active[pos] = 1;
                dsu.activate(pos, a[pos] == globalMax);
                if (pos > 1 && active[pos - 1]) {
                    dsu.unite(pos, pos - 1);
                }
                if (pos < n && active[pos + 1]) {
                    dsu.unite(pos, pos + 1);
                }
                ++j;
            }

            long long bestSizeWithMaximum = dsu.totalIndependent - (dsu.goodComponents > 0 ? 0LL : 1LL);
            answer = max(answer, globalMax + value + bestSizeWithMaximum);
            i = j;
        }

        cout << answer << '\n';
    }

    return 0;
}

