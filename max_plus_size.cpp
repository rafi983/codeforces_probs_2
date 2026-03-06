#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 0;
    if (!(cin >> t)) {
        return 0;
    }

    while (t--) {
        int n = 0;
        cin >> n;

        int maxOdd = 0;
        int maxEven = 0;

        for (int i = 1; i <= n; ++i) {
            int x = 0;
            cin >> x;
            if (i % 2 == 1) {
                maxOdd = max(maxOdd, x);
            } else {
                maxEven = max(maxEven, x);
            }
        }

        int oddCount = (n + 1) / 2;
        int evenCount = n / 2;

        cout << max(maxOdd + oddCount, maxEven + evenCount) << '\n';
    }

    return 0;
}

