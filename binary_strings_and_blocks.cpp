#include <bits/stdc++.h>

using namespace std;

static const int MOD = 998244353;

struct SegmentTree {
    int n = 0;
    vector<int> mx;

    void init(int size) {
        n = size;
        mx.assign(4 * n + 5, 0);
    }

    void build(int node, int left, int right, const vector<int>& a) {
        if (left == right) {
            mx[node] = a[left];
            return;
        }
        int mid = (left + right) / 2;
        build(node * 2, left, mid, a);
        build(node * 2 + 1, mid + 1, right, a);
        mx[node] = max(mx[node * 2], mx[node * 2 + 1]);
    }

    int first_greater(int node, int left, int right, int ql, int value) const {
        if (right < ql || mx[node] <= value) {
            return n + 1;
        }
        if (left == right) {
            return left;
        }
        int mid = (left + right) / 2;
        int res = first_greater(node * 2, left, mid, ql, value);
        if (res != n + 1) {
            return res;
        }
        return first_greater(node * 2 + 1, mid + 1, right, ql, value);
    }

    int first_greater(int ql, int value) const {
        if (ql > n) {
            return n + 1;
        }
        return first_greater(1, 1, n, ql, value);
    }
};

void add_range(vector<int>& diff, int left, int right, int value) {
    if (left > right) {
        return;
    }
    diff[left] += value;
    if (diff[left] >= MOD) {
        diff[left] -= MOD;
    }
    diff[right + 1] -= value;
    if (diff[right + 1] < 0) {
        diff[right + 1] += MOD;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    int changes = n - 1;
    vector<int> req(changes + 1, 0);

    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        req[r - 1] = max(req[r - 1], l);
    }

    SegmentTree st;
    st.init(changes);
    st.build(1, 1, changes, req);

    vector<int> bad(changes + 1, changes + 1);
    for (int last = 0; last <= changes; ++last) {
        bad[last] = st.first_greater(last + 1, last);
    }

    vector<int> diff(changes + 3, 0);
    vector<int> dp(changes + 2, 0);

    add_range(diff, 1, bad[0], 1);

    int active = 0;
    for (int pos = 1; pos <= changes + 1; ++pos) {
        active += diff[pos];
        if (active >= MOD) {
            active -= MOD;
        }
        if (active < 0) {
            active += MOD;
        }
        dp[pos] = active;

        if (pos <= changes) {
            add_range(diff, pos + 1, bad[pos], dp[pos]);
        }
    }

    cout << (2LL * dp[changes + 1]) % MOD << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

