#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    cout << fixed << setprecision(10);

    while (t--) {
        int n;
        cin >> n;

        vector<int> c(n + 1), p(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> c[i] >> p[i];
        }

        long double f_next = 0.0L;

        for (int i = n; i >= 1; --i) {
            long double multiplier = 1.0L - (long double)p[i] / 100.0L;
            long double take = (long double)c[i] + multiplier * f_next;
            long double skip = f_next;
            f_next = max(skip, take);
        }

        cout << (double)f_next << '\n';
    }

    return 0;
}

