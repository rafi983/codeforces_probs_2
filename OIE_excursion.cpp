#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int max_consec = 1;
    int current = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i - 1]) {
            current++;
            if (current > max_consec) {
                max_consec = current;
            }
        } else {
            current = 1;
        }
    }

    if (max_consec >= m) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
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

