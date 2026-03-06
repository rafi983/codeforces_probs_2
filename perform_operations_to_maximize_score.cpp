#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Item {
    ll a;
    int b;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        ll k;
        cin >> n >> k;

        vector<ll> a(n);
        vector<int> b(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) cin >> b[i];

        vector<Item> v(n);
        for (int i = 0; i < n; ++i) v[i] = {a[i], b[i]};
        sort(v.begin(), v.end(), [](const Item& x, const Item& y) {
            if (x.a != y.a) return x.a < y.a;
            return x.b < y.b;
        });

        vector<ll> vals(n);
        for (int i = 0; i < n; ++i) vals[i] = v[i].a;

        ll ans = 0;
        int need = (n + 1) / 2;
        int mid = n / 2;


        for (int i = 0; i < n; ++i) {
            if (v[i].b == 0) continue;
            ll med = (i < mid ? v[mid].a : v[mid - 1].a);
            ans = max(ans, v[i].a + k + med);
        }

        vector<int> eligPos;
        vector<ll> eligVals;
        vector<int> eligRank(n, -1);
        for (int i = 0; i < n; ++i) {
            if (v[i].b == 1) {
                eligRank[i] = (int)eligPos.size();
                eligPos.push_back(i);
                eligVals.push_back(v[i].a);
            }
        }

        vector<ll> prefElig(eligVals.size() + 1, 0);
        for (int i = 0; i < (int)eligVals.size(); ++i) {
            prefElig[i + 1] = prefElig[i] + eligVals[i];
        }

        auto can_make = [&](int idx, ll x) -> bool {
            int r = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
            int already = n - r;
            if (idx >= r) --already;

            if (already >= need) return true;

            int d = need - already;

            int m = (int)(lower_bound(eligPos.begin(), eligPos.end(), r) - eligPos.begin());
            bool removedEligibleBelow = (v[idx].b == 1 && idx < r);
            int available = m - (removedEligibleBelow ? 1 : 0);
            if (available < d) return false;

            ll sumLargest = prefElig[m] - prefElig[m - d];
            if (removedEligibleBelow) {
                int rank = eligRank[idx];
                if (rank >= m - d) {
                    sumLargest -= v[idx].a;
                    sumLargest += eligVals[m - d - 1];
                }
            }

            ll cost = 1LL * d * x - sumLargest;
            return cost <= k;
        };

        ll hi = vals.back() + k;
        for (int i = 0; i < n; ++i) {
            ll lo = 0, curHi = hi;
            while (lo < curHi) {
                ll midX = lo + (curHi - lo + 1) / 2;
                if (can_make(i, midX)) {
                    lo = midX;
                } else {
                    curHi = midX - 1;
                }
            }
            ans = max(ans, v[i].a + lo);
        }

        cout << ans << '\n';
    }

    return 0;
}

