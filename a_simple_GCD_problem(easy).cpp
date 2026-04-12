#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

static long long lcm_ll(long long x, long long y) {
    return x / gcd(x, y) * y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<long long> a(n + 1), b(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) cin >> b[i]; // In easy version, b[i] == a[i].

        vector<long long> g(n, 0);
        for (int i = 1; i <= n - 1; ++i) {
            g[i] = gcd(a[i], a[i + 1]);
        }

        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            long long required;
            if (i == 1) {
                required = g[1];
            } else if (i == n) {
                required = g[n - 1];
            } else {
                required = lcm_ll(g[i - 1], g[i]);
            }

            if (required < a[i]) ++ans;
        }

        cout << ans << '\n';
    }

    return 0;
}

