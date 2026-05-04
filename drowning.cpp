#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> bit;

    Fenwick() : n(0) {}
    explicit Fenwick(int n_) { init(n_); }

    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }

    void add(int idx, long long val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += val;
    }

    long long sum_prefix(int idx) const {
        long long res = 0;
        for (; idx > 0; idx -= idx & -idx) res += bit[idx];
        return res;
    }

    long long sum_range(int l, int r) const {
        if (l > r) return 0;
        return sum_prefix(r) - sum_prefix(l - 1);
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

        vector<long long> a(n + 1), pref(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            long long signed_val = (i % 2 == 1 ? a[i] : -a[i]);
            pref[i] = pref[i - 1] + signed_val;
        }

        vector<long long> vals(pref.begin(), pref.end());
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        auto get_rank = [&](long long x) {
            return (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin()) + 1;
        };

        int m = (int)vals.size();
        Fenwick even_bit(m), odd_bit(m);

        long long odd_seen = 0;
        long long answer = 0;

        even_bit.add(get_rank(pref[0]), 1);

        for (int j = 1; j <= n; ++j) {
            int r = get_rank(pref[j]);

            if (j % 2 == 1) {
                answer += even_bit.sum_prefix(r - 1);
            } else {
                answer += odd_seen - odd_bit.sum_prefix(r);
            }

            if (j % 2 == 0) {
                even_bit.add(r, 1);
            } else {
                odd_bit.add(r, 1);
                ++odd_seen;
            }
        }

        cout << answer << '\n';
    }

    return 0;
}
