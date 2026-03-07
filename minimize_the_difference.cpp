#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

static inline int64 ceil_div(int64 a, int64 b) {
    return (a + b - 1) / b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int64> a(n + 1), pref(n + 1, 0), suff(n + 2, 0);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            pref[i] = pref[i - 1] + a[i];
        }
        for (int i = n; i >= 1; --i) {
            suff[i] = suff[i + 1] + a[i];
        }

        int64 bestMin = LLONG_MAX;
        for (int i = 1; i <= n; ++i) {
            bestMin = min(bestMin, pref[i] / i);
        }

        int64 bestMax = 0;
        for (int i = 1; i <= n; ++i) {
            bestMax = max(bestMax, ceil_div(suff[i], (int64)(n - i + 1)));
        }

        cout << bestMax - bestMin << '\n';
    }

    return 0;
}

