#include <bits/stdc++.h>
using namespace std;

static bool isPowerOfTwo(long long x) {
    return x > 0 && (x & (x - 1)) == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        long long ans = n;
        vector<pair<long long, long long>> cur, nxt;

        for (int i = 0; i + 1 < n; ++i) {
            long long d = llabs(a[i + 1] - a[i]);
            nxt.clear();
            nxt.push_back({d, 1});

            for (const auto &it : cur) {
                long long g = std::gcd(it.first, d);
                if (nxt.back().first == g) {
                    nxt.back().second += it.second;
                } else {
                    nxt.push_back({g, it.second});
                }
            }

            cur.swap(nxt);
            for (const auto &it : cur) {
                long long g = it.first;
                if (g == 0 || isPowerOfTwo(g)) {
                    ans += it.second;
                }
            }
        }

        cout << ans << '\n';
    }

    return 0;
}

