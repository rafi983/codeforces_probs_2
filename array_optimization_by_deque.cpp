#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int n_) : n(n_), bit(n_ + 1, 0) {}
    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += val;
    }
    int sumPrefix(int idx) const {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) res += bit[idx];
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        vector<long long> vals = a;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        Fenwick fw((int)vals.size());
        long long ans = 0;
        int total = 0;
        for (int i = 0; i < n; ++i) {
            int idx = (int)(lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin()) + 1;
            int less = fw.sumPrefix(idx - 1);
            int lessOrEqual = fw.sumPrefix(idx);
            int greater = total - lessOrEqual;
            ans += min(less, greater);
            fw.add(idx, 1);
            ++total;
        }

        cout << ans << '\n';
    }

    return 0;
}

