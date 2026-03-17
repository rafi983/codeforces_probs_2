#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        unordered_map<int, int> freq;
        freq.reserve(n * n * 2);

        int mx = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int x;
                cin >> x;
                int f = ++freq[x];
                if (f > mx) mx = f;
            }
        }

        if (n == 1) {
            cout << "NO\n";
            continue;
        }

        cout << (mx <= n * (n - 1) ? "YES\n" : "NO\n");
    }

    return 0;
}

