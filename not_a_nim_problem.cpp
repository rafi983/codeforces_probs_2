#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> build_spf(int limit, vector<int> &primes) {
    vector<int> spf(limit + 1, 0);
    for (int i = 2; i <= limit; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || 1LL * i * p > limit) {
                break;
            }
            spf[i * p] = p;
        }
    }
    return spf;
}

int grundy(int x, const vector<int> &spf, const vector<int> &primes) {
    if (x == 1) {
        return 1;
    }
    if (x % 2 == 0) {
        return 0;
    }

    int p = spf[x];
    return int(lower_bound(primes.begin(), primes.end(), p) - primes.begin()) + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    vector<vector<int>> tests(t);
    int max_a = 1;

    for (int tc = 0; tc < t; ++tc) {
        int n;
        cin >> n;
        tests[tc].resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> tests[tc][i];
            max_a = max(max_a, tests[tc][i]);
        }
    }

    vector<int> primes;
    vector<int> spf = build_spf(max_a, primes);

    for (const vector<int> &a : tests) {
        int xr = 0;
        for (int x : a) {
            xr ^= grundy(x, spf, primes);
        }
        cout << (xr ? "Alice" : "Bob") << '\n';
    }

    return 0;
}

