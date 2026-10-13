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
        int n = 0;
        cin >> n;
        long long p = 0;
        for (int i = 1; i <= n; ++i) {
            long long a;
            cin >> a;
            p += (i % 2 == 1) ? a : -a;
        }
        cout << p << '\n';
    }

    return 0;
}
