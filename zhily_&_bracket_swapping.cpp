#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string a, b;
        cin >> a >> b;

        int s = 0;
        int L = 0, R = 0;
        int parity = 0;
        bool ok = true;

        for (int i = 0; i < n; ++i) {
            if (a[i] == b[i]) {
                if (a[i] == '(') ++s;
                else --s;
            } else {
                --L;
                ++R;
                parity ^= 1;
            }

            if (s < 0) {
                ok = false;
                break;
            }

            int nl = max(L, -s);
            int nr = min(R, s);

            if ((nl & 1) != parity) ++nl;
            if ((nr & 1) != parity) --nr;

            if (nl > nr) {
                ok = false;
                break;
            }

            L = nl;
            R = nr;
        }

        if (!ok || s != 0 || parity != 0 || L > 0 || R < 0) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }

    return 0;
}
