#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        string s;
        cin >> s;

        int n = stoi(s);
        int root = -1;

        for (int r = 0; r <= 100; ++r) {
            if (r * r == n) {
                root = r;
                break;
            }
        }

        if (root == -1) {
            cout << -1 << '\n';
        } else {
            cout << 0 << ' ' << root << '\n';
        }
    }

    return 0;
}

