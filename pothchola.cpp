#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

inline int get_msb(long long n) {
    if (n == 0) return -1;
    return 63 - __builtin_clzll(n);
}

void solve() {
    int n;
    if (!(cin >> n)) return;

    vector<long long> a(n);
    vector<vector<long long>> buckets(62);
    vector<int> max_dp(62, 0);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        int msb = get_msb(a[i]);
        if (msb >= 0) {
            buckets[msb].push_back(a[i]);
        }
    }

    int overall_max = 0;

    for (int k = 60; k >= 0; --k) {
        if (buckets[k].empty()) continue;


        int length_from_bucket = 1 + max_dp[k];

        if (length_from_bucket > overall_max) {
            overall_max = length_from_bucket;
        }


        for (long long val : buckets[k]) {
            for (int b = 0; b < k; ++b) {
                if ((val >> b) & 1) {
                    if (length_from_bucket > max_dp[b]) {
                        max_dp[b] = length_from_bucket;
                    }
                }
            }
        }
    }

    if (overall_max == 0 && n > 0) overall_max = 1;

    cout << overall_max << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}

