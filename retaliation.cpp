#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    if (!(cin >> n)) return;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    if (n < 2) {
        cout << "NO" << endl;
        return;
    }

    long long D = a[1] - a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] - a[i-1] != D) {
            cout << "NO" << endl;
            return;
        }
    }

    long long num = a[0] - D;
    long long dem = n + 1;

    if (num % dem != 0) {
        cout << "NO" << endl;
        return;
    }

    long long y = num / dem;
    long long x = y + D;

    if (x >= 0 && y >= 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
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

