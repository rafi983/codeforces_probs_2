#include <bits/stdc++.h>
using namespace std;

static long long minK(long long n) {
    long long k = 1;
    for (long long p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            k *= p;
            while (n % p == 0) {
                n /= p;
            }
        }
    }
    if (n > 1) {
        k *= n;
    }
    return k;
}

static void solve(istream& in, ostream& out) {
    int t = 0;
    in >> t;
    while (t--) {
        long long n = 0;
        in >> n;
        out << minK(n) << '\n';
    }
}

#ifndef UNIT_TEST
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve(cin, cout);
    return 0;
}
#endif
