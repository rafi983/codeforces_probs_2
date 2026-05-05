#include <iostream>
#include <vector>
#include <numeric>
#include <cstdlib>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> p(n);
        for (int i = 0; i < n; ++i) cin >> p[i];

        long long ans = 0;
        for (int i = 0; i + 1 < n; ++i) {
            int x = p[i], y = p[i + 1];
            if (abs(x - y) == gcd(x, y)) ++ans;
        }

        cout << ans << '\n';
    }

    return 0;
}
