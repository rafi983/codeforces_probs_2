#include <bits/stdc++.h>
using namespace std;

static bool feasible(long long L, const vector<int>& a) {
    vector<pair<long long, long long>> intervals;
    intervals.push_back({0, L});

    for (int d : a) {
        vector<pair<long long, long long>> next;
        next.reserve(intervals.size() * 2);
        for (auto [l, r] : intervals) {
            long long nl = l + d;
            long long nr = r + d;
            if (nl <= L && nr >= 0) {
                nl = max(nl, 0LL);
                nr = min(nr, L);
                if (nl <= nr) next.push_back({nl, nr});
            }
            nl = l - d;
            nr = r - d;
            if (nl <= L && nr >= 0) {
                nl = max(nl, 0LL);
                nr = min(nr, L);
                if (nl <= nr) next.push_back({nl, nr});
            }
        }
        if (next.empty()) return false;
        sort(next.begin(), next.end());
        vector<pair<long long, long long>> merged;
        merged.reserve(next.size());
        for (auto [l, r] : next) {
            if (merged.empty() || l > merged.back().second) {
                merged.push_back({l, r});
            } else {
                merged.back().second = max(merged.back().second, r);
            }
        }
        intervals.swap(merged);
    }

    return !intervals.empty();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        long long lo = 0, hi = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            lo = max(lo, (long long)a[i]);
            hi += a[i];
        }

        while (lo < hi) {
            long long mid = (lo + hi) / 2;
            if (feasible(mid, a)) hi = mid;
            else lo = mid + 1;
        }

        cout << lo << '\n';
    }

    return 0;
}

