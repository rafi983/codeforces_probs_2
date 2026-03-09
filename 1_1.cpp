#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    string s;
    cin >> n >> s;

    vector<int> pos;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            pos.push_back(i);
        }
    }

    if (pos.empty()) {
        cout << 0 << ' ' << 0 << '\n';
        return;
    }

    int mn = 0, mx = 0;
    int l = pos[0], r = pos[0];

    for (int i = 1; i < (int)pos.size(); ++i) {
        if (pos[i] - pos[i - 1] <= 2) {
            r = pos[i];
        } else {
            int len = r - l + 1;
            mx += len;
            mn += (len + 2) / 2;
            l = r = pos[i];
        }
    }

    int len = r - l + 1;
    mx += len;
    mn += (len + 2) / 2;

    cout << mn << ' ' << mx << '\n';
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

