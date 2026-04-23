#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long x, y;
        cin >> x >> y;

        long long k = y / x;
        cout << (k == 2 ? "NO" : "YES") << '\n';
    }

    return 0;
}

