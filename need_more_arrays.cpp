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

        int groups = 0;
        int last = -1000000000;

        for (int x : a) {
            if (x > last + 1) {
                ++groups;
                last = x;
            }
        }

        cout << groups << '\n';
    }

    return 0;
}

