#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        if (n == 2) {
            cout << 2 << '\n';
        } else if (n == 3) {
            cout << 3 << '\n';
        } else {
            cout << (n % 2) << '\n';
        }
    }

    return 0;
}

