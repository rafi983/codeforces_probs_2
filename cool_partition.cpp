#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct SegmentTree {
    int n;
    vector<int> tree;
    vector<int> lazy;

    SegmentTree(int n) : n(n), tree(4 * n + 1, INF), lazy(4 * n + 1, 0) {}

    void push(int node) {
        if (lazy[node] != 0) {
            tree[2 * node] += lazy[node];
            lazy[2 * node] += lazy[node];
            tree[2 * node + 1] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
            lazy[node] = 0;
        }
    }

    void update(int node, int start, int end, int l, int r, int diff) {
        if (l > end || r < start) return;
        if (l <= start && end <= r) {
            tree[node] += diff;
            lazy[node] += diff;
            return;
        }
        push(node);
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, diff);
        update(2 * node + 1, mid + 1, end, l, r, diff);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    void set(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val; // Direct set, ignoring lazy for this leaf is risky if not careful.

            lazy[node] = 0;
            return;
        }
        push(node);
        int mid = (start + end) / 2;
        if (idx <= mid) set(2 * node, start, mid, idx, val);
        else set(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    int query(int node, int start, int end, int l, int r) {
        if (l > end || r < start) return -1;
        if (tree[node] > 0) return -1;

        if (start == end) return start;

        push(node);
        int mid = (start + end) / 2;
        int res = query(2 * node + 1, mid + 1, end, l, r);
        if (res != -1) return res;
        return query(2 * node, start, mid, l, r);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    SegmentTree st(n);
    map<int, int> last_pos;
    vector<int> dp(n + 1, 0);
    int distinct_count = 0;

    for (int i = 1; i <= n; ++i) {
        int val = a[i];
        if (last_pos.find(val) == last_pos.end()) {
            distinct_count++;
            st.set(1, 1, n, i, distinct_count);
        } else {
            int prev = last_pos[val];
            st.update(1, 1, n, prev, i - 1, -1);
            st.set(1, 1, n, i, distinct_count); // distinct_count is correct here?

        }
        last_pos[val] = i;

        if (i > 1) { // Can query
            int idx = st.query(1, 1, n, 1, i - 1);
            if (idx != -1) {
                dp[i] = dp[idx] + 1;
            } else {
                dp[i] = 1;
            }
        } else {
            dp[i] = 1;
        }
    }
    cout << dp[n] << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

