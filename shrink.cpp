#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

void solve() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << "1" << endl;
        return;
    }
    if (n == 2) {
        cout << "1 2" << endl;
        return;
    }
    cout << "2";
    for (int i = 3; i <= n; ++i) {
        cout << " " << i;
    }
    cout << " 1" << endl;
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

