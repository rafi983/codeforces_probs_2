#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        long long a, b;
        cin >> n >> a >> b;

        long long g = std::gcd(a, b);
        vector<long long> rem(n);
        for (int i = 0; i < n; ++i) {
            long long x;
            cin >> x;
            rem[i] = x % g;
        }

        sort(rem.begin(), rem.end());

        long long maxGap = 0;
        for (int i = 0; i + 1 < n; ++i) {
            maxGap = max(maxGap, rem[i + 1] - rem[i]);
        }
        maxGap = max(maxGap, rem[0] + g - rem.back());

        cout << (g - maxGap) << '\n';
    }

    return 0;
}

