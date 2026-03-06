#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long xc, yc;
        int k;
        cin >> xc >> yc >> k;

        vector<pair<long long, long long>> ans;
        ans.reserve(k);

        if (k % 2 == 1) {
            ans.push_back({xc, yc});
        }

        for (int d = 1; (int)ans.size() < k; ++d) {
            ans.push_back({xc - d, yc - d});
            if ((int)ans.size() < k) {
                ans.push_back({xc + d, yc + d});
            }
        }

        for (auto [x, y] : ans) {
            cout << x << ' ' << y << '\n';
        }
    }

    return 0;
}

