#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        string s;
        cin >> n >> k >> s;

        int zeros = 0;
        for (char c : s) {
            if (c == '0') {
                ++zeros;
            }
        }
        int ones = n - zeros;

        int pairs = n / 2;
        int diff_pairs = pairs - k;

        bool ok = true;
        if (diff_pairs < 0 || diff_pairs > pairs) {
            ok = false;
        }
        if (diff_pairs > zeros || diff_pairs > ones) {
            ok = false;
        }
        if (((zeros - diff_pairs) & 1) != 0) {
            ok = false;
        }

        cout << (ok ? "YES" : "NO") << '\n';
    }

    return 0;
}

