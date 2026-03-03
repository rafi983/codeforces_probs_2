#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    const int B = 1 << 20;

    while (t--) {
        int n, l, r;
        cin >> n >> l >> r;

        vector<int> pref(n + 1, 0);

        for (int i = 0; i < r; ++i) {
            pref[i] = i;
        }

        pref[r] = l - 1;

        for (int i = r + 1; i <= n; ++i) {
            pref[i] = B + i;
        }

        for (int i = 1; i <= n; ++i) {
            int ai = pref[i - 1] ^ pref[i];
            cout << ai << (i == n ? '\n' : ' ');
        }
    }

    return 0;
}

