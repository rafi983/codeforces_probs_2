#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    int first = -1;
    int last = -1;

    for (int i = 0; i < n; ++i) {
        if (s[i] == 'B') {
            if (first == -1) {
                first = i;
            }
            last = i;
        }
    }

    if (first == -1) {
        cout << 0 << endl;
    } else {
        cout << (last - first + 1) << endl;
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

