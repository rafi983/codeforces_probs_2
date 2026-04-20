#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> p(k + 1);
    for (int i = 1; i <= k; i++) {
        cin >> p[i];
    }

    int x = a[p[1]];

    // b[i] = a[i] xor x, target is all zeros in b.
    vector<int> d(n + 2, 0);
    int prev = 0;
    for (int i = 1; i <= n; i++) {
        int bi = a[i] ^ x;
        d[i] = bi ^ prev;
        prev = bi;
    }
    d[n + 1] = prev;

    long long totalOnes = 0;
    long long maxInGroup = 0;

    auto countOnes = [&](int L, int R) {
        long long cnt = 0;
        for (int i = L; i <= R; i++) {
            cnt += d[i];
        }
        return cnt;
    };

    long long c0 = countOnes(1, p[1]);
    totalOnes += c0;
    maxInGroup = max(maxInGroup, c0);

    for (int i = 1; i < k; i++) {
        long long c = countOnes(p[i] + 1, p[i + 1]);
        totalOnes += c;
        maxInGroup = max(maxInGroup, c);
    }

    long long ck = countOnes(p[k] + 1, n + 1);
    totalOnes += ck;
    maxInGroup = max(maxInGroup, ck);

    long long ans = max(totalOnes / 2, maxInGroup);
    cout << ans << '\n';
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

