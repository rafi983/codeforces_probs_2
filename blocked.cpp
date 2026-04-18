#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        sort(a.begin(), a.end());

        bool hasDuplicate = false;
        for (int i = 1; i < n; ++i) {
            if (a[i] == a[i - 1]) {
                hasDuplicate = true;
                break;
            }
        }

        if (hasDuplicate) {
            cout << -1 << '\n';
            continue;
        }

        for (int i = n - 1; i >= 0; --i) {
            cout << a[i] << (i == 0 ? '\n' : ' ');
        }
    }

    return 0;
}

