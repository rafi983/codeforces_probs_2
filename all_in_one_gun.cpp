#include <bits/stdc++.h>

using namespace std;

static long long minimal_time_with_one_swap(int n, long long h, long long k, const vector<long long>& a) {
    long long total = 0;
    for (long long v : a) total += v;

    long long full_magazines = (h - 1) / total;
    long long remaining = h - full_magazines * total;

    vector<long long> prefix(n + 1, 0);

    vector<long long> min_inside(n + 1, (long long)4e18);
    for (int i = 1; i <= n; ++i) {
        prefix[i] = prefix[i - 1] + a[i - 1];
        min_inside[i] = min(min_inside[i - 1], a[i - 1]);
    }

    vector<long long> suffix_max(n + 2, (long long)-4e18);

    for (int i = n; i >= 1; --i) {
        suffix_max[i] = max(suffix_max[i + 1], a[i - 1]);
    }

    int best_len = n;

    for (int len = 1; len <= n; ++len) {

        long long best_prefix = prefix[len];

        if (len < n) {

            long long candidate = prefix[len] - min_inside[len] + suffix_max[len + 1];
            if (candidate > best_prefix) best_prefix = candidate;
        }
        if (best_prefix >= remaining) {
            best_len = len;
            break;
        }
    }

    return full_magazines * (n + k) + best_len;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {

        int n;
        long long h, k;
        cin >> n >> h >> k;

        vector<long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        cout << minimal_time_with_one_swap(n, h, k, a) << '\n';

    }

    return 0;
}
