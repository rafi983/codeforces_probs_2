#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

long long get_answer_for_canonical(long long n, long long k, long long g) {
    if (g == 1) {
        return n + k - 1;
    }

    long long early_missing = (n - 1) * (g - 1);
    if (k <= early_missing) {
        long long block = (k - 1) / (g - 1);
        long long offset = (k - 1) % (g - 1);
        return block * g + offset + 1;
    }

    return (n - 1) * g + (k - early_missing);
}

void solve() {
    int n;
    long long k;
    cin >> n >> k;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    if (n == 1) {
        if (k <= a[0]) {
            cout << k - 1 << '\n';
        } else {
            cout << k << '\n';
        }
        return;
    }

    long long g = a[0];
    for (int i = 1; i < n; ++i) {
        g = gcd(g, a[i]);
    }

    cout << get_answer_for_canonical(n, k, g) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

