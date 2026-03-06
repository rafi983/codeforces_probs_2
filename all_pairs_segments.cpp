#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;

    vector<long long> x(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
    }

    unordered_map<long long, long long> freq;
    freq.reserve(static_cast<size_t>(2 * n + 10));
    freq.max_load_factor(0.7f);

    for (int i = 1; i <= n; ++i) {
        long long coveredAtPoint = 1LL * i * (n - i + 1) - 1;
        ++freq[coveredAtPoint];
    }

    for (int i = 1; i < n; ++i) {
        long long gap = x[i + 1] - x[i] - 1;
        if (gap > 0) {
            long long coveredInsideGap = 1LL * i * (n - i);
            freq[coveredInsideGap] += gap;
        }
    }

    for (int i = 0; i < q; ++i) {
        long long k;
        cin >> k;
        if (i) {
            cout << ' ';
        }
        auto it = freq.find(k);
        cout << (it == freq.end() ? 0LL : it->second);
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

