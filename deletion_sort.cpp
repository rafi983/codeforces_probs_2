#include <bits/stdc++.h>
using namespace std;

static bool is_non_decreasing(const vector<int>& a) {
    for (size_t i = 1; i < a.size(); ++i) {
        if (a[i - 1] > a[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 0;
    if (!(cin >> t)) {
        return 0;
    }
    while (t--) {
        int n = 0;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        if (is_non_decreasing(a)) {
            cout << n << "\n";
        } else {
            cout << 1 << "\n";
        }
    }
    return 0;
}
