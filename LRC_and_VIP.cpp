#include <bits/stdc++.h>

using namespace std;

static int gcd_int(int a, int b) {
    return std::gcd(a, b);
}

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
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        vector<int> prefix(n), suffix(n);
        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                prefix[i] = a[i];
            } else {
                prefix[i] = gcd_int(prefix[i - 1], a[i]);
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            if (i == n - 1) {
                suffix[i] = a[i];
            } else {
                suffix[i] = gcd_int(suffix[i + 1], a[i]);
            }
        }

        int split_index = -1;
        for (int i = 0; i < n; ++i) {
            int gcd_rest = 0;
            if (i > 0) {
                gcd_rest = prefix[i - 1];
            }
            if (i + 1 < n) {
                gcd_rest = (gcd_rest == 0) ? suffix[i + 1] : gcd_int(gcd_rest, suffix[i + 1]);
            }
            if (gcd_rest != a[i]) {
                split_index = i;
                break;
            }
        }

        if (split_index == -1) {
            cout << "No\n";
            continue;
        }

        cout << "Yes\n";
        for (int i = 0; i < n; ++i) {
            if (i == split_index) {
                cout << 1;
            } else {
                cout << 2;
            }
            cout << (i + 1 == n ? '\n' : ' ');
        }
    }

    return 0;
}
