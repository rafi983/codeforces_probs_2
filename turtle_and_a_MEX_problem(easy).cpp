#include <bits/stdc++.h>
using namespace std;

static long long sum_upto(long long x) {
    return x * (x + 1) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        long long m;
        cin >> n >> m;

        int best_second_mex = 0;

        for (int i = 0; i < n; ++i) {
            int l;
            cin >> l;

            vector<char> seen(l + 2, 0);
            for (int j = 0; j < l; ++j) {
                long long x;
                cin >> x;
                if (0 <= x && x <= l + 1) {
                    seen[static_cast<int>(x)] = 1;
                }
            }

            int first_mex = 0;
            while (first_mex <= l + 1 && seen[first_mex]) {
                ++first_mex;
            }

            int second_mex = first_mex + 1;
            while (second_mex <= l + 1 && seen[second_mex]) {
                ++second_mex;
            }

            best_second_mex = max(best_second_mex, second_mex);
        }

        long long M = best_second_mex;
        long long ans;

        if (m <= M) {
            ans = (m + 1) * M;
        } else {
            ans = M * (M + 1) + (sum_upto(m) - sum_upto(M));
        }

        cout << ans << '\n';
    }

    return 0;
}

