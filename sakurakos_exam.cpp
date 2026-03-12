#include <iostream>

using namespace std;

void solve() {
    int a, b;
    cin >> a >> b;

    if (a % 2 != 0) {
        cout << "NO\n";
        return;
    }

    if (a == 0 && b % 2 != 0) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
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

