#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 0;
    if (!(cin >> t)) {
        return 0;
    }
    while (t--) {
        long long n, m, p, q;
        cin >> n >> m >> p >> q;

        if (n % p == 0) {
            long long periods = n / p;
            long long required = periods * q;
            cout << (m == required ? "YES" : "NO") << '\n';
        } else {
            cout << "YES" << '\n';
        }
    }

    return 0;
}
