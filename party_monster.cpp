#include <bits/stdc++.h>
using namespace std;

void solve(istream& in, ostream& out) {
    int t;
    if (!(in >> t)) {
        return;
    }
    while (t--) {
        int n;
        string s;
        in >> n >> s;
        int openCount = 0;
        for (char c : s) {
            if (c == '(') {
                openCount++;
            }
        }
        int closeCount = n - openCount;
        out << (openCount == closeCount ? "YES" : "NO") << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve(cin, cout);
    return 0;
}
