#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class SegTreeMin {
public:
    SegTreeMin() : n(0) {}

    explicit SegTreeMin(int size) {
        init(size);
    }

    void init(int size) {
        n = 1;
        while (n < size) n <<= 1;
        tree.assign(2 * n, INF);
    }

    void build(const vector<int>& a) {
        int sz = static_cast<int>(a.size()) - 1;
        for (int i = 1; i <= sz; ++i) {
            tree[n + i - 1] = a[i];
        }
        for (int i = n - 1; i >= 1; --i) {
            tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    void point_set(int pos, int val) {
        int idx = n + pos - 1;
        tree[idx] = val;
        idx >>= 1;
        while (idx >= 1) {
            tree[idx] = min(tree[idx << 1], tree[idx << 1 | 1]);
            idx >>= 1;
        }
    }

    int range_min(int l, int r) const {
        int left = n + l - 1;
        int right = n + r - 1;
        int ans = INF;

        while (left <= right) {
            if (left & 1) ans = min(ans, tree[left++]);
            if (!(right & 1)) ans = min(ans, tree[right--]);
            left >>= 1;
            right >>= 1;
        }
        return ans;
    }

private:
    static constexpr int INF = numeric_limits<int>::max();
    int n;
    vector<int> tree;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }

        SegTreeMin st(n);
        st.build(a);

        while (q--) {
            int type;
            cin >> type;

            if (type == 1) {
                int i, x;
                cin >> i >> x;
                st.point_set(i, x);
            } else {
                int l, r;
                cin >> l >> r;

                int len = r - l;

                auto f = [&](int d) -> int {
                    return st.range_min(l, l + d) - d;
                };

                if (f(len) > 0) {
                    cout << 0 << '\n';
                    continue;
                }

                int lo = 0;
                int hi = len;
                while (lo < hi) {
                    int mid = lo + (hi - lo) / 2;
                    if (f(mid) <= 0) {
                        hi = mid;
                    } else {
                        lo = mid + 1;
                    }
                }

                cout << (f(lo) == 0 ? 1 : 0) << '\n';
            }
        }
    }

    return 0;
}

