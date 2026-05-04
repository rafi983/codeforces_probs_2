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
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];

        Fenwick cnt_left(n), sum_left(n);
        long long total_cnt_left = 0, total_sum_left = 0;

        long long base = 0;
        for (int i = 1; i <= n; ++i) {
            int x = a[i];
            long long cnt_le = cnt_left.sum_prefix(x);
            long long sum_le = sum_left.sum_prefix(x);

            long long cnt_gt = total_cnt_left - cnt_le;
            long long sum_gt = total_sum_left - sum_le;
            base += sum_gt - cnt_gt * x;

            cnt_left.add(x, 1);
            sum_left.add(x, x);
            ++total_cnt_left;
            total_sum_left += x;
        }

        Fenwick left_counts(n), right_counts(n);
        for (int i = 1; i <= n; ++i) right_counts.add(a[i], 1);

        long long answer = base;
        for (int p = 1; p <= n; ++p) {
            int x = a[p];

            right_counts.add(x, -1);

            long long left_ge_x = (p - 1) - left_counts.sum_prefix(x - 1);
            long long right_le_x_minus_1 = right_counts.sum_prefix(x - 1);
            long long delta = left_ge_x - right_le_x_minus_1;

            answer = max(answer, base + delta);

            left_counts.add(x, 1);
        }

        cout << answer << '\n';
    }

    return 0;
}
