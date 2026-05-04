#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 998244353;
static const int MAXF = 2000005;

long long mod_pow(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e > 0) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<long long> fact(MAXF, 1);
    for (int i = 1; i < MAXF; ++i) fact[i] = (fact[i - 1] * i) % MOD;

    const long long inv2 = mod_pow(2, MOD - 2);

    int t;
    cin >> t;

    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<int> cnt(n + 1, 0);
        for (int v = 1; v <= n; ++v) ++cnt[gcd(v, n)];

        vector<int> req(n + 1, 0);
        vector<int> assigned(n + 1, 0);

        long long ways_fixed = 1;
        int free_non_n = n - 1;
        long long pos_sum = 1LL * n * (n - 1) / 2 % MOD;

        long long pair_avg = 1LL * (n - 1) * (n - 2) % MOD;
        pair_avg = pair_avg * inv2 % MOD;
        pair_avg = pair_avg * inv2 % MOD;

        bool bad = false;

        for (int qi = 0; qi < q; ++qi) {
            int idx, x;
            cin >> idx >> x;
            --idx;

            assigned[idx] = x;

            if (!bad) {
                if (x == n) {
                    pos_sum = (n - 1 - idx) % MOD;
                } else {
                    --free_non_n;
                    if (req[n] == 0) {
                        pos_sum = (pos_sum - (n - 1 - idx)) % MOD;
                        if (pos_sum < 0) pos_sum += MOD;
                    }
                }

                ++req[x];
                if (req[x] > cnt[x]) {
                    bad = true;
                } else {
                    ways_fixed = ways_fixed * (cnt[x] - req[x] + 1) % MOD;
                }
            }

            if (bad) {
                cout << 0 << '\n';
                continue;
            }

            long long place_n_choices = (req[n] == 0 ? (free_non_n + 1) : 1);
            long long total_ways = ways_fixed * fact[free_non_n] % MOD;
            long long inv_sum = (pair_avg * place_n_choices + pos_sum) % MOD;
            long long ans = total_ways * inv_sum % MOD;

            cout << ans << '\n';
        }
    }

    return 0;
}
