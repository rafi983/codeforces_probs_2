#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <climits>
using namespace std;

using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        int total_gcd = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            total_gcd = gcd(total_gcd, a[i]);
        }

        int cur = 0;
        int used = 0;
        int64 ans = 0;

        while (cur != total_gcd) {
            int nxt = INT_MAX;
            for (int x : a) {
                nxt = min(nxt, gcd(cur, x));
            }
            cur = nxt;
            ans += cur;
            ++used;
        }

        ans += 1LL * (n - used) * total_gcd;
        cout << ans << '\n';
    }

    return 0;
}
