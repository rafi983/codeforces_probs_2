#include <bits/stdc++.h>
using namespace std;

static bool can_make_median(long long v, const vector<long long>& absvals) {

    int n = static_cast<int>(absvals.size());
    int k = (n + 1) / 2;
    int less_fixed = 0;
    int flexible = 0;

    for (int i = 1; i < n; ++i) {
        long long y = absvals[i];
        long long minVal = -y;
        long long maxVal = y;
        if (maxVal < v) {
            ++less_fixed;
        } else if (minVal > v) {
        } else {
            ++flexible;
        }
    }

    int need_less = k - 1;
    return (less_fixed <= need_less) && (need_less <= less_fixed + flexible);
}

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
        vector<long long> absvals(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            absvals[i] = llabs(a[i]);
        }

        long long v1 = a[0];
        long long v2 = -a[0];
        bool ok = can_make_median(v1, absvals) || can_make_median(v2, absvals);
        cout << (ok ? "YES" : "NO") << '\n';

    }

    return 0;
}
