#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n, x, y;
    cin >> n;
    cin >> x >> y;

    long long rate = min(x, y);
    cout << (n + rate - 1) / rate << '\n';
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

