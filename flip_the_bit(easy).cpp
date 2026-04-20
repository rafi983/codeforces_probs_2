#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int p1;
    cin >> p1;
    p1--;
    int cL = 0;
    for (int i = 0; i < p1; i++) {
        if (a[i] != a[i + 1]) cL++;
    }
    int cR = 0;
    for (int i = p1; i < n - 1; i++) {
        if (a[i] != a[i + 1]) cR++;
    }
    int L = (cL % 2 == 1) ? cL + 1 : cL;
    int R = (cR % 2 == 1) ? cR + 1 : cR;
    cout << max(L, R) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
