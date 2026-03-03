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

        vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());

        int best = 1;
        int cur = 1;

        for (int i = 1; i < (int)a.size(); ++i) {
            if (a[i] == a[i - 1] + 1) {
                ++cur;
            } else {
                cur = 1;
            }
            best = max(best, cur);
        }

        cout << best << '\n';
    }

    return 0;
}

