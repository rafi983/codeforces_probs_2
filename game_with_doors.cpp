#include <iostream>
#include <algorithm>

using namespace std;

void solve() {
    int l, r, L, R;
    cin >> l >> r >> L >> R;

    int left = max(l, L);
    int right = min(r, R);

    if (left > right) {
        cout << 1 << '\n';
        return;
    }

    int answer = right - left;
    if (l != L) {
        ++answer;
    }
    if (r != R) {
        ++answer;
    }

    cout << answer << '\n';
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

