#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> positionsByDeadline(n + 1);
    for (int i = 1; i <= n; ++i) {
        int a;
        cin >> a;
        positionsByDeadline[a].push_back(i);
    }

    int leftMost = n + 1;
    int rightMost = 0;
    int lo = 1;
    int hi = n;

    for (int time = 1; time <= n; ++time) {
        for (int pos : positionsByDeadline[time]) {
            leftMost = min(leftMost, pos);
            rightMost = max(rightMost, pos);
        }

        if (rightMost == 0) {
            continue;
        }

        if (rightMost - leftMost + 1 > time) {
            cout << 0 << '\n';
            return;
        }

        lo = max(lo, rightMost - time + 1);
        hi = min(hi, leftMost + time - 1);
    }

    cout << max(0, hi - lo + 1) << '\n';
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

