#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int m;
    cin >> m;
    while (m--) {
        string s;
        cin >> s;

        if ((int)s.size() != n) {
            cout << "NO\n";
            continue;
        }

        unordered_map<int, int> last_value_pos;
        last_value_pos.reserve(n * 2);
        vector<int> last_char_pos(26, -1);

        bool ok = true;
        for (int i = 0; i < n; ++i) {
            int value_pos = -1;
            auto it = last_value_pos.find(a[i]);
            if (it != last_value_pos.end()) {
                value_pos = it->second;
            }

            int ch = s[i] - 'a';
            if (value_pos != last_char_pos[ch]) {
                ok = false;
                break;
            }

            last_value_pos[a[i]] = i;
            last_char_pos[ch] = i;
        }

        cout << (ok ? "YES" : "NO") << '\n';
    }
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

