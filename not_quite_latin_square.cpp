#include <iostream>
#include <string>

using namespace std;

void solve() {

    for (int i = 0; i < 3; ++i) {
        string s;
        cin >> s;
        bool hasA = false, hasB = false, hasC = false;
        bool hasQ = false;

        for (char c : s) {
            if (c == 'A') hasA = true;
            else if (c == 'B') hasB = true;
            else if (c == 'C') hasC = true;
            else if (c == '?') hasQ = true;
        }

        if (hasQ) {
            if (!hasA) cout << "A\n";
            else if (!hasB) cout << "B\n";
            else if (!hasC) cout << "C\n";
        }
    }
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