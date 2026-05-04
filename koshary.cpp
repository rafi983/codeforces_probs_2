#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) {
        return 0;
    }
    while (t--) {
        int x, y;
        cin >> x >> y;
        bool bothOdd = (x % 2 != 0) && (y % 2 != 0);
        cout << (bothOdd ? "NO" : "YES") << '\n';
    }
    return 0;
}

