#include <bits/stdc++.h>
using namespace std;

static long long f(long long C) {
    long long s = 0;
    for (long long i = 1; i <= C; ++i) s += i * (C / i);
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 0;
    if (!(cin >> t)) {
        return 0;
    }

    while (t--) {
        long long n;
        cin >> n;
        long long l = 1, r = n;
        while (l < r) {
            long long m = (l + r) / 2;
            if (f(m) >= n) r = m;
            else l = m + 1;
        }
        long long C = l;

        string out;
        long long rem = n, bag = 0;
        for (long long i = C; i >= 1 && rem > 0; --i) {
            long long cnt = min(C / i, rem / i);
            for (long long j = 0; j < cnt; ++j) {
                ++bag;
                for (long long k = 0; k < i; ++k) {
                    out += to_string(bag);
                    out += ' ';
                }
            }
            rem -= cnt * i;
        }
        cout << C << '\n' << out << '\n';
    }

    return 0;
}
