#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<long long> prefix(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> prefix[i];
        prefix[i] += prefix[i - 1];
    }

    long long total_boundaries = 1LL * n * (n + 1) * (n - 1) / 6;

    vector<long long> pair_sums;
    pair_sums.reserve(1LL * n * (n + 1) / 2);
    for (int i = 0; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            pair_sums.push_back(prefix[i] + prefix[j]);
        }
    }

    sort(pair_sums.begin(), pair_sums.end());

    vector<long long> values;
    vector<int> counts;
    values.reserve(pair_sums.size());
    counts.reserve(pair_sums.size());

    long long preserved_boundaries = 0;
    for (int i = 0; i < (int)pair_sums.size(); ) {
        int j = i;
        while (j < (int)pair_sums.size() && pair_sums[j] == pair_sums[i]) {
            ++j;
        }

        int cnt = j - i;
        preserved_boundaries += 1LL * cnt * (cnt - 1);
        values.push_back(pair_sums[i]);
        counts.push_back(cnt);
        i = j;
    }

    for (int k = 1; k < n; ++k) {
        long long target = 2 * prefix[k];
        auto it = lower_bound(values.begin(), values.end(), target);
        if (it != values.end() && *it == target) {
            int pos = int(it - values.begin());
            preserved_boundaries += counts[pos];
        }
    }

    cout << (total_boundaries - preserved_boundaries) << '\n';
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

