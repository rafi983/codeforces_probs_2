#include <iostream>
#include <vector>
using namespace std;

const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    int max_a = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] > max_a) {
            max_a = a[i];
        }
    }

    vector<int> spf(max_a + 1);
    for (int i = 0; i <= max_a; ++i) {
        spf[i] = i;
    }
    for (int i = 2; i * i <= max_a; ++i) {
        if (spf[i] != i) {
            continue;
        }
        for (int j = i * i; j <= max_a; j += i) {
            if (spf[j] == j) {
                spf[j] = i;
            }
        }
    }

    vector<int> sum_by_product(max_a + 1, 0);
    vector<int> dp(n, 0);

    for (int i = 0; i < n; ++i) {
        vector<int> primes;
        int x = a[i];
        while (x > 1) {
            int p = spf[x];
            primes.push_back(p);
            while (x % p == 0) {
                x /= p;
            }
        }

        int subsets = 1 << primes.size();
        if (i == 0) {
            dp[i] = 1;
        } else {
            long long ways = 0;
            for (int mask = 1; mask < subsets; ++mask) {
                int product = 1;
                int bits = 0;
                for (int bit = 0; bit < (int)primes.size(); ++bit) {
                    if (mask & (1 << bit)) {
                        product *= primes[bit];
                        ++bits;
                    }
                }

                if (bits % 2 == 1) {
                    ways += sum_by_product[product];
                } else {
                    ways -= sum_by_product[product];
                }
            }
            ways %= MOD;
            if (ways < 0) {
                ways += MOD;
            }
            dp[i] = (int)ways;
        }

        for (int mask = 1; mask < subsets; ++mask) {
            int product = 1;
            for (int bit = 0; bit < (int)primes.size(); ++bit) {
                if (mask & (1 << bit)) {
                    product *= primes[bit];
                }
            }
            sum_by_product[product] += dp[i];
            if (sum_by_product[product] >= MOD) {
                sum_by_product[product] -= MOD;
            }
        }
    }

    cout << dp[n - 1] << '\n';
    return 0;
}

