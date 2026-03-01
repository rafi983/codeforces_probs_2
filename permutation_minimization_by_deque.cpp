#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        cin >> n;
        deque<int> dq;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            if (dq.empty() || x < dq.front()) dq.push_front(x);
            else dq.push_back(x);
        }
        for (int i = 0; i < n; ++i) {
            cout << dq[i] << (i + 1 == n ? '\n' : ' ');
        }
    }

    return 0;
}

