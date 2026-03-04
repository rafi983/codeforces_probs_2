#include <bits/stdc++.h>
using namespace std;

struct FenwickMax {
    int n;
    vector<int> bit;

    FenwickMax() : n(0) {}
    explicit FenwickMax(int n_) { init(n_); }

    void init(int n_) {
        n = n_;
        bit.assign(n + 1, -1);
    }

    void reset() {
        fill(bit.begin(), bit.end(), -1);
    }

    void update(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) {
            bit[idx] = max(bit[idx], val);
        }
    }

    int query(int idx) const {
        int res = -1;
        for (; idx > 0; idx -= idx & -idx) {
            res = max(res, bit[idx]);
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    for (int i = 0; i < n; ++i) cin >> c[i];

    vector<int> uniq_b = b;
    sort(uniq_b.begin(), uniq_b.end());
    uniq_b.erase(unique(uniq_b.begin(), uniq_b.end()), uniq_b.end());

    vector<int> b_id(n);
    for (int i = 0; i < n; ++i) {
        b_id[i] = int(lower_bound(uniq_b.begin(), uniq_b.end(), b[i]) - uniq_b.begin());
    }

    int colors_cnt = (int)uniq_b.size();
    int full_mask = (1 << m) - 1;

    vector<FenwickMax> fw(1 << m);
    for (int mask = 0; mask <= full_mask; ++mask) {
        fw[mask].init(n);
    }

    vector<int> color_of_b(colors_cnt);
    vector<int> col_i(n);

    const int ITER = 320;
    mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(0, m - 1);

    int best = -1;

    for (int it = 0; it < ITER; ++it) {
        for (int id = 0; id < colors_cnt; ++id) {
            color_of_b[id] = dist(rng);
        }
        for (int i = 0; i < n; ++i) {
            col_i[i] = color_of_b[b_id[i]];
        }

        for (int mask = 0; mask <= full_mask; ++mask) {
            fw[mask].reset();
        }

        for (int i = 0; i < n; ++i) {
            int bit = 1 << col_i[i];
            int ai = a[i];
            int ci = c[i];

            int dp_val[1 << 5];
            for (int mask = 0; mask <= full_mask; ++mask) dp_val[mask] = -1;

            dp_val[bit] = ci;

            for (int mask = 1; mask <= full_mask; ++mask) {
                if ((mask & bit) == 0 || mask == bit) continue;
                int prev = fw[mask ^ bit].query(ai);
                if (prev >= 0) {
                    dp_val[mask] = max(dp_val[mask], prev + ci);
                }
            }

            for (int mask = 1; mask <= full_mask; ++mask) {
                if (dp_val[mask] >= 0) {
                    fw[mask].update(ai, dp_val[mask]);
                }
            }
        }

        best = max(best, fw[full_mask].query(n));
    }

    cout << best << '\n';
    return 0;
}

