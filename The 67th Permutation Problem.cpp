#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << " " << n + 1 + 2 * i << " " << n + 2 + 2 * i << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}
