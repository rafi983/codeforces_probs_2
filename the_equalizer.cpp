#include <iostream>
using namespace std;

void solve() {
    int n;
    long long k;
    cin >> n >> k;
    long long s = 0;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        s += a;
    }
    if (s % 2 != 0 || (n * k) % 2 == 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
