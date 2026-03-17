#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        string s;
        cin >> n >> s;

        vector<int> seen(n, 0);
        int pos = 0;
        seen[pos] = 1;

        for (int step = 0; step < n; ++step) {
            if (s[pos] == 'R') {
                ++pos;
            } else {
                --pos;
            }
            seen[pos] = 1;
        }

        int ans = 0;
        for (int x : seen) ans += x;
        cout << ans << '\n';
    }

    return 0;
}

