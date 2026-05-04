#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        vector<int> even_vals, odd_vals;
        even_vals.reserve(n);
        odd_vals.reserve(n);

        for (int x : a) {
            if (x % 2 == 0) even_vals.push_back(x);
            else odd_vals.push_back(x);
        }

        const int INF = (int)1e9;
        int even_min = INF, even_max = -INF;
        int odd_min = INF, odd_max = -INF;

        for (int x : even_vals) {
            even_min = min(even_min, x);
            even_max = max(even_max, x);
        }
        for (int x : odd_vals) {
            odd_min = min(odd_min, x);
            odd_max = max(odd_max, x);
        }

        bool ok = true;

        if (even_vals.size() > 1) {
            int pref_max = even_vals[0];
            for (int i = 1; i < (int)even_vals.size(); ++i) {
                int x = even_vals[i];
                if (pref_max > x) {
                    if (odd_min > x && odd_max < pref_max) {
                        ok = false;
                        break;
                    }
                } else {
                    pref_max = x;
                }
            }
        }

        if (ok && odd_vals.size() > 1) {
            int pref_max = odd_vals[0];
            for (int i = 1; i < (int)odd_vals.size(); ++i) {
                int x = odd_vals[i];
                if (pref_max > x) {
                    if (even_min > x && even_max < pref_max) {
                        ok = false;
                        break;
                    }
                } else {
                    pref_max = x;
                }
            }
        }

        cout << (ok ? "YES" : "NO") << '\n';
    }

    return 0;
}
