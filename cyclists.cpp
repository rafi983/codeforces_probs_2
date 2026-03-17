#include <bits/stdc++.h>
using namespace std;

static long long sumSmallest(vector<int> v, int need) {
    if (need <= 0) return 0;
    if (need >= (int)v.size()) {
        long long s = 0;
        for (int x : v) s += x;
        return s;
    }
    nth_element(v.begin(), v.begin() + need, v.end());
    long long s = 0;
    for (int i = 0; i < need; ++i) s += v[i];
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k, p, m;
        cin >> n >> k >> p >> m;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];

        const int winCost = a[p];

        // Cost before the first possible play of win-card.
        long long prepFirst = 0;
        if (p > k) {
            vector<int> pref;
            pref.reserve(p - 1);
            for (int i = 1; i < p; ++i) pref.push_back(a[i]);
            prepFirst = sumSmallest(pref, p - k);
        }

        // Cost between two consecutive plays of win-card.
        vector<int> others;
        others.reserve(n - 1);
        for (int i = 1; i <= n; ++i) {
            if (i != p) others.push_back(a[i]);
        }
        long long prepCycle = sumSmallest(others, n - k);

        long long firstPlayCost = prepFirst + winCost;
        long long repeatCost = prepCycle + winCost;

        if (firstPlayCost > m) {
            cout << 0 << '\n';
            continue;
        }

        long long ans = 1;
        long long rem = m - firstPlayCost;
        if (repeatCost > 0) ans += rem / repeatCost;

        cout << ans << '\n';
    }

    return 0;
}


