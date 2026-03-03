#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAX_BITS = 31;
    vector<vector<long long>> c(MAX_BITS + 1, vector<long long>(MAX_BITS + 1, 0));
    for (int i = 0; i <= MAX_BITS; ++i) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }

    int t;
    cin >> t;

    while (t--) {
        long long n, k;
        cin >> n >> k;

        int d = 0;
        while ((1LL << d) < n) {
            ++d;
        }

        long long canWin = 0;

        for (int len = 1; len <= d; ++len) {
            long long maxExtraOnes = k - len;
            if (maxExtraOnes < 0) continue;

            int limit = static_cast<int>(maxExtraOnes);
            if (limit > len - 1) limit = len - 1;

            for (int ones = 0; ones <= limit; ++ones) {
                canWin += c[len - 1][ones];
            }
        }

        if (k >= d + 1) {
            ++canWin;
        }

        cout << (n - canWin) << '\n';
    }

    return 0;
}

