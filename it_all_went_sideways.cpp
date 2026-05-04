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

        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];

        vector<int> freq(n + 2, 0);
        for (int i = 1; i <= n; ++i) ++freq[a[i]];

        vector<int> k(n + 2, 0);
        for (int h = n; h >= 1; --h) k[h] = k[h + 1] + freq[h];

        vector<int> min_suffix(n + 2, n + 1);
        min_suffix[n] = a[n];
        for (int i = n - 1; i >= 1; --i) min_suffix[i] = min(min_suffix[i + 1], a[i]);

        vector<int> suffix_ones(n + 2, 0);
        for (int h = 1; h <= n; ++h) {
            int lo = 1, hi = n, first = n + 1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (min_suffix[mid] >= h) {
                    first = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            if (first <= n) suffix_ones[h] = n - first + 1;
        }

        long long base = 0;
        for (int h = 1; h <= n; ++h) base += (long long)k[h] - suffix_ones[h];

        long long answer = base;
        for (int p = 1; p <= n; ++p) {
            int h = a[p];
            int s = suffix_ones[h];
            int start = n - s + 1;

            long long delta = -1;
            if (p >= start) delta = p - start;

            answer = max(answer, base + delta);
        }

        cout << answer << '\n';
    }

    return 0;
}
