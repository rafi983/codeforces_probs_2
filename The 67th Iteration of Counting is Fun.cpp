#include <iostream>
#include <vector>
using namespace std;

static const long long MOD = 676767677;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<int> b(n + 1);
        vector<int> cnt(m, 0);
        for (int i = 1; i <= n; ++i) {
            cin >> b[i];
            ++cnt[b[i]];
        }

        vector<int> pref(m + 1, 0);
        for (int tme = 1; tme <= m; ++tme) {
            pref[tme] = pref[tme - 1] + cnt[tme - 1];
        }

        long long ans = 1;
        bool ok = true;

        for (int i = 1; i <= n && ok; ++i) {
            int tme = b[i];

            if (tme == 0) {
                continue;
            }

            int nb = 1e9;
            if (i > 1) nb = min(nb, b[i - 1]);
            if (i < n) nb = min(nb, b[i + 1]);

            if (nb == 1e9) {
                ok = false;
                break;
            }

            int q = nb + 1;
            if (q > tme) {
                ok = false;
                break;
            }

            long long ways = 0;
            if (q == tme) {
                ways = pref[tme];
            } else {
                ways = pref[tme] - pref[tme - 1];
            }

            if (ways <= 0) {
                ok = false;
                break;
            }

            ans = (ans * (ways % MOD)) % MOD;
        }

        if (!ok) cout << 0 << '\n';
        else cout << ans << '\n';
    }

    return 0;
}
