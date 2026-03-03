#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long s, k, m;
        cin >> s >> k >> m;

        long long flips = m / k;
        long long afterLastFlip = m % k;
        long long ans;

        if (k >= s) {
            ans = s - afterLastFlip;
            if (ans < 0) ans = 0;
        } else {
            long long remainAtLastFlip = (flips % 2 == 0) ? s : k;
            ans = remainAtLastFlip - afterLastFlip;
        }

        cout << ans << '\n';
    }

    return 0;
}

