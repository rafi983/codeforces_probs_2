#include <iostream>
#include <vector>

using namespace std;

const long long MOD = 1000000007;

long long mod_pow(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = result * base % MOD;
        }
        base = base * base % MOD;
        exp /= 2;
    }
    return result;
}

void solve() {
    int n;
    cin >> n;

    long long prefix_sum = 0;
    long long pair_sum = 0;

    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        x %= MOD;
        pair_sum = (pair_sum + x * prefix_sum) % MOD;
        prefix_sum = (prefix_sum + x) % MOD;
    }

    long long total_pairs = 1LL * n * (n - 1) / 2;
    long long answer = pair_sum * mod_pow(total_pairs % MOD, MOD - 2) % MOD;
    cout << answer << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

