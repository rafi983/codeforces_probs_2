#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

void solve() {
    int sum = 0, mx = -100;
    for (int i = 0; i < 7; i++) {
        int x;
        cin >> x;
        sum += x;
        mx = max(mx, x);
    }
    cout << 2 * mx - sum << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
