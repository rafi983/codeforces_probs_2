#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> p(n + 1), inv(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> p[i];
            inv[p[i]] = i;
        }

        vector<int> safePref(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            safePref[i] = safePref[i - 1] + (p[i] <= i ? 1 : 0);
        }

        vector<int> diff(n + 3, 0);
        for (int j = 1; j <= n; ++j) {
            if (p[j] > j) {
                int l = j + 1;
                int r = p[j];
                ++diff[l];
                --diff[r + 1];
            }
        }

        vector<int> activeForward(n + 2, 0);
        for (int m = 1; m <= n; ++m) {
            activeForward[m] = activeForward[m - 1] + diff[m];
        }

        int ans = safePref[n];

        for (int m = 2; m <= n; ++m) {
            if (inv[m] < m) {
                int cur = safePref[m - 1] + activeForward[m];
                if (cur > ans) ans = cur;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}

