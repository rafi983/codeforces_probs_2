#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int l, r;
        cin >> l >> r;

        int oddCount = (r + 1) / 2 - (l / 2);

        cout << (oddCount / 2) << '\n';
    }
    return 0;
}

