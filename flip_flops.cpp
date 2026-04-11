#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    long long c, k;
    cin >> n >> c >> k;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    for (int i = 0; i < n; ++i) {
        if (a[i] <= c) {
            long long d = min(k, c - a[i]);
            c += a[i] + d;
            k -= d;
        } else {
            break;
        }
    }

    cout << c << "\n";
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
