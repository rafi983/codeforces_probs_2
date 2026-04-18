#include <iostream>
#include <vector>

using namespace std;

void solve() {
    long long p, q;
    cin >> p >> q;

    long long S = p + 2 * q;
    long long target = 2 * S + 1;

    long long best_n = -1, best_m = -1;

    for (long long k = 3; k * k <= target; k += 2) {
        if (target % k == 0) {
            long long k2 = target / k;
            long long n = (k - 1) / 2;
            long long m = (k2 - 1) / 2;

            if (n >= 1 && m >= 1) {
                long long max_L = min(n * (m + 1), m * (n + 1));
                if (q <= max_L) {
                    best_n = n;
                    best_m = m;
                }
            }
        }
    }

    if (best_n != -1) {
        cout << best_n << " " << best_m << "\n";
    } else {
        cout << "-1\n";
    }
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

