#include <iostream>
#include <vector>
#include <set>
using namespace std;

static bool can_make_mex_k(const vector<int>& a, int k) {
    multiset<int> ms(a.begin(), a.end());

    for (int x = k - 1; x >= 0; --x) {
        auto it = ms.find(x);
        if (it != ms.end()) {
            ms.erase(it);
        } else {
            if (ms.empty()) return false;
            auto jt = prev(ms.end());
            if (*jt < 2 * x + 1) return false;
            ms.erase(jt);
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        int lo = 0, hi = n + 1;
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if (can_make_mex_k(a, mid)) lo = mid;
            else hi = mid;
        }

        cout << lo << '\n';
    }

    return 0;
}
