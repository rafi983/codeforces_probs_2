#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    long long k;
    cin >> n >> k;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    long long answer = (n % 2 == 1 ? a[0] : 0LL);
    long long gap_sum = 0;

    for (int i = n % 2; i + 1 < n; i += 2) {
        gap_sum += a[i + 1] - a[i];
    }

    answer += max(0LL, gap_sum - k);
    cout << answer << '\n';
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

