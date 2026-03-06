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

        if (n < 5) {
            cout << -1 << '\n';
            continue;
        }

        vector<int> ans;
        for (int x = 1; x <= n; x += 2) {
            if (x != 5) {
                ans.push_back(x);
            }
        }
        ans.push_back(5);
        ans.push_back(4);
        for (int x = 2; x <= n; x += 2) {
            if (x != 4) {
                ans.push_back(x);
            }
        }

        for (int i = 0; i < n; ++i) {
            if (i) {
                cout << ' ';
            }
            cout << ans[i];
        }
        cout << '\n';
    }

    return 0;
}

