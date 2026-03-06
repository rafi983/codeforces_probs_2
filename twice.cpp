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

        vector<int> cnt(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            ++cnt[x];
        }

        int ans = 0;
        for (int x = 1; x <= n; ++x) {
            ans += cnt[x] / 2;
        }

        cout << ans << '\n';
    }

    return 0;
}

