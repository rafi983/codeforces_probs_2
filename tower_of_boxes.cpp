#include <iostream>

using namespace std;

void solve() {
    long long n, m, d;
    cin >> n >> m >> d;

    long long max_height = (d / m) + 1;
    long long min_towers = (n + max_height - 1) / max_height;

    cout << min_towers << endl;
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

