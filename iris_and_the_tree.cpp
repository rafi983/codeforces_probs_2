#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p;
    vector<int> sz;
    vector<vector<int>> members;

    explicit DSU(int n) : p(n + 1), sz(n + 1, 1), members(n + 1) {
        for (int i = 1; i <= n; ++i) {
            p[i] = i;
            members[i].push_back(i);
        }
    }

    int find(int x) {
        if (p[x] == x) {
            return x;
        }
        return p[x] = find(p[x]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        long long w;
        cin >> n >> w;

        vector<int> par(n + 1, 0);
        for (int v = 2; v <= n; ++v) {
            cin >> par[v];
        }

        vector<pair<int, long long>> events(n - 1);
        for (int i = 0; i < n - 1; ++i) {
            int x;
            long long y;
            cin >> x >> y;
            events[i] = {x, y};
        }

        DSU dsu(n);
        long long knownSum = 0;
        long long connectedPairs = 0;

        auto nxt = [n](int v) {
            return (v == n ? 1 : v + 1);
        };
        auto prv = [n](int v) {
            return (v == 1 ? n : v - 1);
        };

        for (int i = 0; i < n - 1; ++i) {
            int x = events[i].first;
            long long y = events[i].second;
            knownSum += y;

            int a = dsu.find(x);
            int b = dsu.find(par[x]);
            if (a != b) {
                if (dsu.sz[a] > dsu.sz[b]) {
                    swap(a, b);
                }

                long long add = 0;
                for (int v : dsu.members[a]) {
                    if (dsu.find(nxt(v)) == b) {
                        ++add;
                    }
                    if (dsu.find(prv(v)) == b) {
                        ++add;
                    }
                }
                connectedPairs += add;

                dsu.p[a] = b;
                dsu.sz[b] += dsu.sz[a];
                dsu.members[b].insert(dsu.members[b].end(), dsu.members[a].begin(), dsu.members[a].end());
                vector<int>().swap(dsu.members[a]);
            }

            long long rem = w - knownSum;
            long long ans = 2LL * knownSum + (static_cast<long long>(n) - connectedPairs) * rem;
            cout << ans << (i + 1 == n - 1 ? '\n' : ' ');
        }
    }

    return 0;
}

