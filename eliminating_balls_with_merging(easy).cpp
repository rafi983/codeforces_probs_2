#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, x;
        cin >> n >> x;

        vector<ll> a(n + 1), pref(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            pref[i] = pref[i - 1] + a[i];
        }

        int answer = 0;

        for (int start = 1; start <= n; ++start) {
            int l = start, r = start;
            ll sum = a[start];

            while (true) {
                int nl = l;
                int nr = r;

                if (l > 1) {
                    ll need = pref[l - 1] - sum;
                    int pos = int(lower_bound(pref.begin(), pref.begin() + l, need) - pref.begin());
                    nl = pos + 1;
                }

                if (r < n) {
                    ll limit = pref[r] + sum;
                    int pos = int(upper_bound(pref.begin() + r, pref.end(), limit) - pref.begin()) - 1;
                    nr = pos;
                }

                if (nl == l && nr == r) {
                    break;
                }

                l = nl;
                r = nr;
                sum = pref[r] - pref[l - 1];
            }

            if (l == 1 && r == n) {
                ++answer;
            }
        }

        cout << answer << '\n';
    }

    return 0;
}

