#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    long long L = 1;
    bool L_oo = false;
    long long limit_val = n + m;

    for (long long x : a) {
        long long g = std::gcd(x, L);
        L = (L / g) * x;
        if (L > limit_val) {
            L_oo = true;
            break;
        }
    }

    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    vector<bool> can_be_div(limit_val + 1, false);
    for (int x : a) {
        if (x == 0) continue;
        if (x > limit_val) continue;
        if (can_be_div[x]) continue;

        for (int k = x; k <= limit_val; k += x) {
            can_be_div[k] = true;
        }
    }

    vector<int> b(m);
    for(int &x : b) cin >> x;

    int nA = 0;
    int nB = 0;
    int nBoth = 0;

    for(int y : b) {
        bool alice_can = false;
        if (y <= limit_val && can_be_div[y]) {
            alice_can = true;
        }

        bool bob_cannot = false;
        if (!L_oo && (y % L == 0)) {
            bob_cannot = true;
        }

        bool bob_can = !bob_cannot;

        if (alice_can && bob_can) {
            nBoth++;
        } else if (alice_can && !bob_can) {
            nA++;
        } else if (!alice_can && bob_can) {
            nB++;
        }
    }

    if (nBoth % 2 == 1) {
        if (nA >= nB) cout << "Alice\n";
        else cout << "Bob\n";
    } else {
        if (nA > nB) cout << "Alice\n";
        else cout << "Bob\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
