#include <bits/stdc++.h>
using namespace std;

static long long prefixMaxSum(const vector<int>& a) {
    long long total = 0;
    int currentMax = 0;
    for (int x : a) {
        currentMax = max(currentMax, x);
        total += currentMax;
    }
    return total;
}

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

        long long best = prefixMaxSum(a);

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                swap(a[i], a[j]);
                best = max(best, prefixMaxSum(a));
                swap(a[i], a[j]);
            }
        }

        cout << best << '\n';
    }

    return 0;
}

