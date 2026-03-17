#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

static int64 safe_lcm(int64 x, int64 y) {
    int64 g = std::gcd(x, y);
    i128 v = (i128)(x / g) * (i128)y;
    return (int64)v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int64 a, b, c, m;
        cin >> a >> b >> c >> m;

        int64 A = m / a;
        int64 B = m / b;
        int64 C = m / c;

        int64 ab = safe_lcm(a, b);
        int64 ac = safe_lcm(a, c);
        int64 bc = safe_lcm(b, c);
        int64 abc = safe_lcm(ab, c);

        int64 AB = m / ab;
        int64 AC = m / ac;
        int64 BC = m / bc;
        int64 ABC = m / abc;

        int64 alice = 6 * A - 3 * AB - 3 * AC + 2 * ABC;
        int64 bob = 6 * B - 3 * AB - 3 * BC + 2 * ABC;
        int64 carol = 6 * C - 3 * AC - 3 * BC + 2 * ABC;

        cout << alice << ' ' << bob << ' ' << carol << '\n';
    }

    return 0;
}

