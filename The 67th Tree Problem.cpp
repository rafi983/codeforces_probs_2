#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int x, y;
        cin >> x >> y;
        int n = x + y;

        bool ok = true;
        if (x > n / 2) ok = false;
        if ((n % 2 == 0) && x == 0) ok = false;

        if (!ok) {
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";

        int pairs = (n % 2 == 0 ? x - 1 : x);
        int singles = n - 1 - 2 * pairs;

        vector<pair<int, int>> edges;
        edges.reserve(n - 1);

        int cur = 2;
        for (int i = 0; i < pairs; ++i) {
            int u = cur++;
            int v = cur++;
            edges.push_back({1, u});
            edges.push_back({u, v});
        }

        for (int i = 0; i < singles; ++i) {
            int u = cur++;
            edges.push_back({1, u});
        }

        for (auto &e : edges) {
            cout << e.first << ' ' << e.second << '\n';
        }
    }

    return 0;
}
