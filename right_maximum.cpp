#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        int prefMax = 0;
        int operations = 0;

        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            if (x >= prefMax) {
                ++operations;
                prefMax = x;
            }
        }

        cout << operations << '\n';
    }

    return 0;
}

