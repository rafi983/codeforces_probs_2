#include <bits/stdc++.h>
using namespace std;

static int max_blocks_after_rotation(const string &s) {
    const int n = static_cast<int>(s.size());
    if (n == 0) {
        return 0;
    }

    int transitions = 0;
    bool has_equal_adjacent = false;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        if (s[i] != s[j]) {
            transitions++;
        } else {
            has_equal_adjacent = true;
        }
    }

    return transitions + (has_equal_adjacent ? 1 : 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 0;
    if (!(cin >> t)) {
        return 0;
    }
    while (t--) {
        int n = 0;
        string s;
        cin >> n >> s;
        cout << max_blocks_after_rotation(s) << '\n';
    }

    return 0;
}
