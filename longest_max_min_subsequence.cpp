#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<int> mx, mn;
    static constexpr int NEG_INF = -1000000000;
    static constexpr int POS_INF = 1000000000;

    explicit SegTree(const vector<int>& a) {
        n = (int)a.size() - 1;
        mx.assign(4 * n + 5, NEG_INF);
        mn.assign(4 * n + 5, POS_INF);
        build(1, 1, n, a);
    }

    void build(int p, int l, int r, const vector<int>& a) {
        if (l == r) {
            mx[p] = mn[p] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(p << 1, l, m, a);
        build(p << 1 | 1, m + 1, r, a);
        pull(p);
    }

    void pull(int p) {
        mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
        mn[p] = min(mn[p << 1], mn[p << 1 | 1]);
    }

    void update(int idx, int val, int p, int l, int r) {
        if (l == r) {
            mx[p] = mn[p] = val;
            return;
        }
        int m = (l + r) >> 1;
        if (idx <= m) update(idx, val, p << 1, l, m);
        else update(idx, val, p << 1 | 1, m + 1, r);
        pull(p);
    }

    void update(int idx, int val) {
        update(idx, val, 1, 1, n);
    }

    void deactivate(int idx) {
        update(idx, NEG_INF, 1, 1, n);
        // Set mn at leaf to +INF as well.
        setMinInf(idx, 1, 1, n);
    }

    void setMinInf(int idx, int p, int l, int r) {
        if (l == r) {
            mn[p] = POS_INF;
            return;
        }
        int m = (l + r) >> 1;
        if (idx <= m) setMinInf(idx, p << 1, l, m);
        else setMinInf(idx, p << 1 | 1, m + 1, r);
        pull(p);
    }

    int queryMax(int ql, int qr, int p, int l, int r) const {
        if (qr < l || r < ql) return NEG_INF;
        if (ql <= l && r <= qr) return mx[p];
        int m = (l + r) >> 1;
        return max(queryMax(ql, qr, p << 1, l, m), queryMax(ql, qr, p << 1 | 1, m + 1, r));
    }

    int queryMin(int ql, int qr, int p, int l, int r) const {
        if (qr < l || r < ql) return POS_INF;
        if (ql <= l && r <= qr) return mn[p];
        int m = (l + r) >> 1;
        return min(queryMin(ql, qr, p << 1, l, m), queryMin(ql, qr, p << 1 | 1, m + 1, r));
    }

    int queryMax(int l, int r) const {
        return queryMax(l, r, 1, 1, n);
    }

    int queryMin(int l, int r) const {
        return queryMin(l, r, 1, 1, n);
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

        vector<vector<int>> pos(n + 1);
        vector<int> last(n + 1, -1);
        for (int i = 1; i <= n; ++i) {
            pos[a[i]].push_back(i);
            last[a[i]] = i;
        }

        multiset<int> lastSet;
        int distinct = 0;
        for (int v = 1; v <= n; ++v) {
            if (!pos[v].empty()) {
                lastSet.insert(last[v]);
                ++distinct;
            }
        }

        SegTree st(a);
        vector<int> ans;
        ans.reserve(distinct);

        int cur = 1;
        for (int step = 1; step <= distinct; ++step) {
            int limit = *lastSet.begin();
            int chosen = (step & 1) ? st.queryMax(cur, limit) : st.queryMin(cur, limit);

            if (chosen <= 0 || chosen > n) {
                // Defensive guard against invalid sentinel selections.
                break;
            }

            auto itPos = lower_bound(pos[chosen].begin(), pos[chosen].end(), cur);
            if (itPos == pos[chosen].end()) {
                break;
            }

            ans.push_back(chosen);
            int idx = *itPos;
            cur = idx + 1;

            auto itLast = lastSet.find(last[chosen]);
            if (itLast != lastSet.end()) {
                lastSet.erase(itLast);
            }

            for (int p : pos[chosen]) {
                st.deactivate(p);
            }
        }

        cout << ans.size() << '\n';
        for (int i = 0; i < (int)ans.size(); ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }

    return 0;
}
