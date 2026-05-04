#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<int> mn, lazy;

    SegTree() : n(0) {}
    explicit SegTree(int n_) { init(n_); }

    void init(int n_) {
        n = n_;
        mn.assign(4 * n + 5, 0);
        lazy.assign(4 * n + 5, 0);
    }

    void push(int p) {
        if (lazy[p] == 0) return;
        for (int c : {p << 1, p << 1 | 1}) {
            mn[c] += lazy[p];
            lazy[c] += lazy[p];
        }
        lazy[p] = 0;
    }

    void add(int p, int l, int r, int ql, int qr, int val) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            mn[p] += val;
            lazy[p] += val;
            return;
        }
        push(p);
        int m = (l + r) >> 1;
        add(p << 1, l, m, ql, qr, val);
        add(p << 1 | 1, m + 1, r, ql, qr, val);
        mn[p] = min(mn[p << 1], mn[p << 1 | 1]);
    }

    int queryMin(int p, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return INT_MAX;
        if (ql <= l && r <= qr) return mn[p];
        push(p);
        int m = (l + r) >> 1;
        return min(queryMin(p << 1, l, m, ql, qr), queryMin(p << 1 | 1, m + 1, r, ql, qr));
    }

    void add(int l, int r, int val) {
        if (l > r) return;
        add(1, 0, n, l, r, val);
    }

    int queryMin(int l, int r) {
        if (l > r) return 0;
        return queryMin(1, 0, n, l, r);
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

        vector<int> a(n);
        int mx = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            mx = max(mx, a[i]);
        }

        int limit = max(n, mx) + 2;
        vector<int> cnt(limit, 0);

        SegTree st(n + 2);

        auto add_offer = [&](int value, int delta) {
            if (value <= 0) return;
            int r = (value - 1) / 2;
            if (r > n + 1) r = n + 1;
            if (r >= 0) st.add(0, r, delta);
        };

        int mex = 0;
        vector<int> ans(n);

        for (int i = 0; i < n; ++i) {
            int v = a[i];

            if (v < mex && cnt[v] == 0) {
                st.add(0, v, +1);
            } else {
                add_offer(v, +1);
            }
            ++cnt[v];

            int pref_len = i + 1;
            while (mex < pref_len) {
                int x = mex;

                if (x < limit && cnt[x] > 0) {
                    add_offer(x, -1);
                } else {
                    st.add(0, x, -1);
                }

                ++mex;

                if (st.queryMin(0, mex - 1) < 0) {
                    --mex;
                    if (x < limit && cnt[x] > 0) {
                        add_offer(x, +1);
                    } else {
                        st.add(0, x, +1);
                    }
                    break;
                }
            }

            ans[i] = mex;
        }

        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }

    return 0;
}
