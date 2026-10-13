#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 0;
    if (!(cin >> t)) {
        return 0;
    }

    while (t--) {
        int n;
        cin >> n;
        vector<int> res;
        if (n == 2) {
            res = {3, 3, 3};
        } else {
            vector<int> E, O;
            for (int v = 2 * n - 2; v >= 4; v -= 2) E.push_back(v);
            for (int v = 2 * n - 1; v >= 3; v -= 2) O.push_back(v);
            auto add = [&](const vector<int> &x) { res.insert(res.end(), x.begin(), x.end()); };
            if (n % 3 == 2) {
                add(E); add(O); add(E);
            } else {
                add(E); add(E); add(E);
            }
        }
        cout << res.size() << '\n';
        for (int v : res) cout << v << ' ';
        cout << '\n';
    }

    return 0;
}
