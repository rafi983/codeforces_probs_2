#include <iostream>
#include <numeric>

using namespace std;

static void solve() {
    long long n, m, a, b;
    cin >> n >> m >> a >> b;

    long long gna = gcd(n, a);
    long long gmb = gcd(m, b);
    long long gnm = gcd(n, m);

    if (gna == 1 && gmb == 1 && (gnm == 1 || gnm == 2)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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

