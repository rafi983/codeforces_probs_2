#include <iostream>

using namespace std;

void solve() {
    long long x, y;
    cin >> x >> y;

    if ((x - 2 * y) % 3 != 0) {
        cout << "NO" << endl;
        return;
    }

    long long K = (x - 2 * y) / 3;

    if (K < 0) {
        cout << "NO" << endl;
        return;
    }


    long long min_c = 0;
    if (-y > 0) min_c = -y;

    if (2 * min_c <= K) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
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
