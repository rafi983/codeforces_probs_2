#include <bits/stdc++.h>

using namespace std;

static void solve(istream &in, ostream &out) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 0;
    in >> t;
    while (t--) {
        int n = 0;
        long long k = 0;
        in >> n >> k;

        vector<long long> a(n);
        long long sum = 0;
        long long mn = LLONG_MAX;
        long long mx = LLONG_MIN;

        for (int i = 0; i < n; ++i) {
            in >> a[i];
            sum += a[i];
            mn = min(mn, a[i]);
            mx = max(mx, a[i]);
        }

        long long maxCount = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i] == mx) {
                ++maxCount;
            }
        }

        long long range = mx - mn;
        string winner;

        if (k == 0) {
            if (range == 1 && maxCount == 1) {
                winner = "Tom";
            } else {
                winner = "Jerry";
            }
        } else {
            if (range > k + 1) {
                winner = "Jerry";
            } else if (range == k + 1 && maxCount > 1) {
                winner = "Jerry";
            } else {
                winner = (sum % 2 == 1) ? "Tom" : "Jerry";
            }
        }

        out << winner << '\n';
    }
}

int main() {
    solve(cin, cout);
    return 0;
}
