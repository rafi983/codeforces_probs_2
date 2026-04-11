#include <iostream>
#include <cstdlib>

using namespace std;

void solve() {
    int n;
    if (!(cin >> n)) exit(0);

    int ans = -1;

    auto ask = [&](int u, int v) {
        cout << "? " << u << " " << v << endl;
        int res;
        if (!(cin >> res) || res == -1) exit(0);
        return res;
    };

    if (ask(1, 2) == 1) ans = 1;
    else if (ask(2, 3) == 1) ans = 2;
    else if (ask(3, 1) == 1) ans = 3;
    else {
        for (int i = 1; i <= n - 2; ++i) {
            if (ask(2 * i + 2, 2 * i + 3) == 1) {
                ans = 2 * i + 2;
                break;
            }
        }
    }

    if (ans == -1) ans = 2 * n;

    cout << "! " << ans << endl;
}

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
