#include <iostream>

using namespace std;

void solve() {
    long long s, m;
    cin >> s >> m;

    long long n = -1;


    long long low = 1, high = s;
    long long ans = -1;


    auto check = [&](long long limit) {
        long long current_s = s;
        for (int j = 60; j >= 0; --j) {
            if ((m >> j) & 1) {

                long long num = current_s >> j;
                long long take = min(limit, num);
                current_s -= take * (1LL << j);
            }
        }
        return current_s == 0;
    };

    if (!check(s)) {
        cout << -1 << "\n";
        return;
    }

    ans = s;

    while(low <= high) {
        long long mid = low + (high - low) / 2;
        if(check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << ans << "\n";
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

