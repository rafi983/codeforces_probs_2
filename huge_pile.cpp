#include <iostream>

using namespace std;

static long long min_time_to_get_k(long long n, long long k) {
    for (long long d = 0; d <= 60; ++d) {
        long long pow2 = 1LL << d;
        long long low = n / pow2;
        long long high = (n + pow2 - 1) / pow2;

        if (k == low || k == high) {
            return d;
        }

        if (low == 0 && high == 0) {
            break;
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long n, k;
        cin >> n >> k;
        cout << min_time_to_get_k(n, k) << '\n';
    }

    return 0;
}

