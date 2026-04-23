#include <iostream>

using namespace std;

static const long long MOD = 998244353;

long long countModClass(long long l, long long r, int c) {
    if (l > r) return 0;
    long long shift = (c - (l % 4) + 4) % 4;
    long long first = l + shift;
    if (first > r) return 0;
    return (r - first) / 4 + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long n, x;
        cin >> n >> x;

        long long leftZero = 1 + countModClass(1, x - 1, 3);
        long long leftOne = countModClass(0, x - 1, 1);
        long long rightZero = countModClass(x, n, 3);
        long long rightOne = countModClass(x, n, 1);

        __int128 part0 = (__int128)(leftZero % MOD) * (rightZero % MOD);
        __int128 part1 = (__int128)(leftOne % MOD) * (rightOne % MOD);
        long long ans = (long long)((part0 + part1) % MOD);

        cout << ans << '\n';
    }

    return 0;
}

