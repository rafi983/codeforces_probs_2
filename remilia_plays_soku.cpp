#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long n, x1, x2, k;
        cin >> n >> x1 >> x2 >> k;

        long long diff = llabs(x1 - x2);
        long long d = min(diff, n - diff);

        if (n <= 3) {
            cout << 1 << '\n';
        } else {
            cout << d + k << '\n';
        }
    }

    return 0;
}
