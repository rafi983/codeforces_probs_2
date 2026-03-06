#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        ll x;
        cin >> n >> k >> x;

        vector<ll> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());

        auto count_allowed = [&](ll d) -> ll {
            if (d == 0) {
                return x + 1;
            }

            ll blocked = 0;
            ll curL = -1, curR = -1;

            for (ll pos : a) {
                ll L = max(0LL, pos - d + 1);
                ll R = min(x, pos + d - 1);
                if (L > R) {
                    continue;
                }
                if (curL == -1) {
                    curL = L;
                    curR = R;
                } else if (L > curR + 1) {
                    blocked += curR - curL + 1;
                    curL = L;
                    curR = R;
                } else {
                    curR = max(curR, R);
                }
            }

            if (curL != -1) {
                blocked += curR - curL + 1;
            }
            return (x + 1) - blocked;
        };

        ll lo = 0, hi = x + 1;
        while (lo < hi) {
            ll mid = lo + (hi - lo + 1) / 2;
            if (count_allowed(mid) >= k) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        ll best = lo;

        vector<pair<ll, ll>> forbidden;
        if (best > 0) {
            for (ll pos : a) {
                ll L = max(0LL, pos - best + 1);
                ll R = min(x, pos + best - 1);
                if (L <= R) {
                    forbidden.push_back({L, R});
                }
            }
        }

        vector<pair<ll, ll>> merged;
        for (auto [L, R] : forbidden) {
            if (merged.empty() || L > merged.back().second + 1) {
                merged.push_back({L, R});
            } else {
                merged.back().second = max(merged.back().second, R);
            }
        }

        vector<ll> ans;
        ans.reserve(k);
        ll cur = 0;
        for (auto [L, R] : merged) {
            while (cur < L && (int)ans.size() < k) {
                ans.push_back(cur);
                ++cur;
            }
            cur = max(cur, R + 1);
            if ((int)ans.size() == k) {
                break;
            }
        }
        while (cur <= x && (int)ans.size() < k) {
            ans.push_back(cur);
            ++cur;
        }

        for (int i = 0; i < k; ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }

    return 0;
}

