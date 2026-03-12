#include <iostream>

using namespace std;

void solve() {
    long long l, r;
    cin >> l >> r;

    long long span = r - l;
    long long low = 1, high = 50000, ans = 1;

    while (low <= high) {
        long long mid = (low + high) / 2;
        long long need = mid * (mid - 1) / 2;

        if (need <= span) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << ans << '\n';
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

