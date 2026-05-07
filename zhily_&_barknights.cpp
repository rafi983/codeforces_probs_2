#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

static const long long MOD = 998244353;

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

struct Frac {
    int num;
    int den;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<long long> a(n), b(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) cin >> b[i];

        if (n == 1) {
            cout << 0 << '\n';
            continue;
        }

        vector<Frac> ratios;
        ratios.reserve(1LL * n * (n - 1));
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (u == v) continue;
                ratios.push_back({(int)b[v], (int)b[u]});
            }
        }

        sort(ratios.begin(), ratios.end(), [](const Frac& x, const Frac& y) {
            return (__int128)x.num * y.den < (__int128)y.num * x.den;
        });

        long long numerator = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                long long qnum = a[i];
                long long qden = a[j];

                int lo = 0, hi = (int)ratios.size();
                while (lo < hi) {
                    int mid = (lo + hi) >> 1;
                    const Frac& f = ratios[mid];
                    if ((__int128)f.num * qden < (__int128)qnum * f.den) lo = mid + 1;
                    else hi = mid;
                }
                numerator += lo;
            }
        }

        numerator %= MOD;
        long long denom = 1LL * n * (n - 1) % MOD;
        long long ans = numerator * mod_pow(denom, MOD - 2) % MOD;
        cout << ans << '\n';
    }

    return 0;
}
