#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        string s;
        cin >> s;

        bool ok = false;
        if (s.size() >= 3 && s[0] == '1' && s[1] == '0' && s[2] != '0') {
            string exponent = s.substr(2);
            ok = exponent.size() > 1 || exponent[0] >= '2';
        }

        cout << (ok ? "YES" : "NO") << '\n';
    }

    return 0;
}

