#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 0;
    if (!(cin >> t)) {
        return 0;
    }

    while (t--) {
        int n = 0;
        cin >> n;
        vector<long long> a(n);
        for (auto &x : a) cin >> x;

        long long lo = a[0], hi = a[0], ans = a[0];
        for (int i = 1; i < n; ++i) {
            ans = max(ans, a[i] + max(llabs(lo), llabs(hi)));
            long long nlo = LLONG_MAX, nhi = LLONG_MIN;
            for (long long s : {lo, hi}) {
                for (long long v : {a[i] - s, a[i], a[i] + s}) {
                    nlo = min(nlo, s + v);
                    nhi = max(nhi, s + v);
                }
            }
            lo = nlo;
            hi = nhi;
        }
        cout << ans << '\n';
    }

    return 0;
}
