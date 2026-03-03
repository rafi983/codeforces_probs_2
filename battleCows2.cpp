#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;

    Fenwick() : n(0) {}
    explicit Fenwick(int n_) { init(n_); }

    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }

    void add(int idx, int delta) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += delta;
    }

    int sumPrefix(int idx) const {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) res += bit[idx];
        return res;
    }

    int lowerBoundByPrefix(int target) const {
        int idx = 0;
        int mask = 1;
        while ((mask << 1) <= n) mask <<= 1;
        for (int step = mask; step > 0; step >>= 1) {
            int nxt = idx + step;
            if (nxt <= n && bit[nxt] < target) {
                idx = nxt;
                target -= bit[nxt];
            }
        }
        return idx + 1;
    }
};

static long long countLeftInterval(
    int L,
    int R,
    int thr,
    int m,
    const Fenwick &fw
) {
    if (L > R || thr < 0) return 0;
    if (thr >= m) return (long long)R - L + 1;

    int need = m - thr;
    int pos = fw.lowerBoundByPrefix(need);
    int minX = pos + 1;
    int start = max(L, minX);
    if (start > R) return 0;
    return (long long)R - start + 1;
}

static long long countRightInterval(
    int L,
    int R,
    int need,
    const vector<int> &suffBad
) {
    if (L > R || need < 0) return 0;

    auto f = [&](int x) {
        return suffBad[x + 1];
    };

    if (f(R) > need) return 0;
    if (f(L) <= need) return (long long)R - L + 1;

    int lo = L, hi = R;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (f(mid) <= need) hi = mid;
        else lo = mid + 1;
    }
    return (long long)R - lo + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<long long> a(n + 1), pref(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            pref[i] = pref[i - 1] + a[i];
        }

        vector<long long> val(n + 1);
        vector<int> bad(n + 2, 0), suffBad(n + 3, 0);
        for (int j = 1; j <= n; ++j) {
            val[j] = a[j] - pref[j - 1];
            if (j >= 2 && val[j] > 0) bad[j] = 1;
        }
        for (int j = n; j >= 1; --j) suffBad[j] = suffBad[j + 1] + bad[j];

        vector<pair<long long, int>> byVal;
        byVal.reserve(n);
        for (int j = 1; j <= n; ++j) byVal.push_back({val[j], j});
        sort(byVal.begin(), byVal.end(), [](const auto &x, const auto &y) {
            if (x.first != y.first) return x.first > y.first;
            return x.second < y.second;
        });

        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 1);
        sort(idx.begin(), idx.end(), [&](int i, int j) {
            if (a[i] != a[j]) return a[i] > a[j];
            return i < j;
        });

        Fenwick fw(n);
        int ptr = 0;
        vector<long long> ans(n + 1, 0);

        for (int id : idx) {
            while (ptr < n && byVal[ptr].first > a[id]) {
                fw.add(byVal[ptr].second, 1);
                ++ptr;
            }

            int m = fw.sumPrefix(id - 1);
            int tail = suffBad[id + 1];
            int T0 = k - tail;

            int rNoCheatLeft = int(lower_bound(pref.begin(), pref.begin() + id, a[id]) - pref.begin()) - 1;
            int p = rNoCheatLeft + 1;

            long long leftGood = 0;
            leftGood += countLeftInterval(1, p, T0, m, fw);
            leftGood += countLeftInterval(p + 1, id, T0 - 1, m, fw);

            long long rightGood = 0;
            int rNoCheatRight = int(lower_bound(pref.begin() + 1, pref.begin() + n + 1, 2 * a[id]) - pref.begin()) - 1;

            int L1 = id + 1;
            int R1 = min(n, rNoCheatRight);
            rightGood += countRightInterval(L1, R1, k, suffBad);

            int L2 = max(id + 1, rNoCheatRight + 1);
            int R2 = n;
            rightGood += countRightInterval(L2, R2, k - 1, suffBad);

            ans[id] = leftGood + rightGood;
        }

        for (int i = 1; i <= n; ++i) {
            cout << ans[i] << (i == n ? '\n' : ' ');
        }
    }

    return 0;
}

