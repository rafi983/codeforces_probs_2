#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int MAXN = 2005;

static int mn[MAXN][MAXN];
static ll row_pref[MAXN][MAXN];
static ll col_suf[MAXN][MAXN];

void solve() {
    int n;
    int h;
    cin >> n >> h;

    vector<int> water(n + 1);
    for (int i = 1; i <= n; ++i) {
        int a;
        cin >> a;
        water[i] = h - a;
    }

    vector<ll> left_sum(n + 1, 0), right_sum(n + 1, 0);

    for (int l = 1; l <= n; ++l) {
        int cur = INT_MAX;
        ll pref = 0;
        for (int r = l; r <= n; ++r) {
            cur = min(cur, water[r]);
            mn[l][r] = cur;
            pref += cur;
            row_pref[l][r] = pref;
            right_sum[l] += cur;
        }
    }

    for (int r = 1; r <= n; ++r) {
        ll suf = 0;
        for (int l = r; l >= 1; --l) {
            suf += mn[l][r];
            col_suf[r][l] = suf;
            left_sum[r] += mn[l][r];
        }
    }

    ll answer = 0;

    for (int k = 1; k <= n; ++k) {
        if (water[k] == 0) {
            continue;
        }
        answer = max(answer, left_sum[k] + right_sum[k] - water[k]);
    }

    for (int p = 1; p <= n; ++p) {
        if (water[p] == 0) {
            continue;
        }
        for (int q = p + 1; q <= n; ++q) {
            if (water[q] == 0) {
                continue;
            }

            int lo = p;
            int hi = q;
            int split = p - 1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (mn[p][mid] >= mn[mid][q]) {
                    split = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }

            ll total = (left_sum[p] - water[p]) + (right_sum[q] - water[q]);
            if (split >= p) {
                total += row_pref[p][split];
            }
            if (split + 1 <= q) {
                total += col_suf[q][split + 1];
            }

            answer = max(answer, total);
        }
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

