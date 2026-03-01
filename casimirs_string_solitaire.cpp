#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        string s;
        cin >> s;
        int a = 0, b = 0, c = 0;
        for (char ch : s) {
            if (ch == 'A') ++a;
            else if (ch == 'B') ++b;
            else if (ch == 'C') ++c;
        }
        if (b == a + c) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}

