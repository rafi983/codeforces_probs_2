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

        for (int x = n; x >= 1; --x) {
            cout << x << (x == 1 ? '\n' : ' ');
        }
    }

    return 0;
}

