#include <iostream>
#include <vector>
using namespace std;

static const long long MOD = 998244353;

static long long mod_pow(long long a, long long e) {
    long long r = 1;
    while (e > 0) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

static vector<long long> fact(1, 1), invfact(1, 1);

static void ensure_fact(int n) {
    int cur = (int)fact.size() - 1;
    if (cur >= n) return;

    fact.resize(n + 1);
    for (int i = cur + 1; i <= n; ++i) fact[i] = fact[i - 1] * i % MOD;

    invfact.resize(n + 1);
    invfact[n] = mod_pow(fact[n], MOD - 2);
    for (int i = n; i > cur; --i) invfact[i - 1] = invfact[i] * i % MOD;
}

static long long C(long long n, long long r) {
    if (r < 0 || r > n) return 0;
    ensure_fact((int)n);
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];

        int op, l, r;
        long long m;
        cin >> op >> l >> r >> m;

        long long fixed_sum = 0;
        int k = 0;
        for (int i = l; i <= r; ++i) {
            if (a[i] == -1) ++k;
            else fixed_sum += a[i];
        }

        long long R = m - fixed_sum;
        if (R < 0) {
            cout << 0 << '\n';
            continue;
        }

        if (k == 0) {
            if (R != 0) {
                cout << 0 << '\n';
                continue;
            }

            long long pref = 0;
            long long ans = 0;
            for (int i = l; i <= r; ++i) {
                pref += a[i];
                long long pm = pref % MOD;
                ans = (ans + pm * pm) % MOD;
            }
            cout << ans << '\n';
            continue;
        }

        long long N = C(R + k - 1, k - 1);
        long long B = C(R + k - 1, k);
        long long A = C(R + k - 1, k + 1);

        long long ans = 0;
        long long pref_fixed = 0;
        long long u = 0;

        for (int i = l; i <= r; ++i) {
            if (a[i] == -1) ++u;
            else pref_fixed += a[i];

            long long F = pref_fixed % MOD;
            long long um = u % MOD;

            long long sumY = um * B % MOD;
            long long sumY2 = (um * ((u + 1) % MOD) % MOD) * A % MOD;
            sumY2 = (sumY2 + um * B) % MOD;

            long long term = N * (F * F % MOD) % MOD;
            term = (term + 2LL * F % MOD * sumY) % MOD;
            term = (term + sumY2) % MOD;

            ans += term;
            if (ans >= MOD) ans -= MOD;
        }

        cout << ans % MOD << '\n';
    }

    return 0;
}
