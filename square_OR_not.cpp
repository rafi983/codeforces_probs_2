#include <iostream>
#include <string>
#include <cmath>

using namespace std;

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    int side = static_cast<int>(sqrt(n));
    if (side * side != n) {
        cout << "No\n";
        return;
    }

    for (int i = 0; i < n; ++i) {
        int row = i / side;
        int col = i % side;
        char expected = (row == 0 || row == side - 1 || col == 0 || col == side - 1) ? '1' : '0';
        if (s[i] != expected) {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

