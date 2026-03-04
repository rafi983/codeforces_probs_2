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

        vector<int> freq(n + 1, 0);
        int best = 0;

        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            ++freq[x];
            best = max(best, freq[x]);
        }

        cout << (n - best) << '\n';
    }

    return 0;
}

