#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<long long> ArrayToRearrange(n);
        long long mx = 0;
        for (int i = 0; i < n; ++i) {
            cin >> ArrayToRearrange[i];
            mx = max(mx, ArrayToRearrange[i]);
        }

        long long sum_max = 1LL * n * mx;

        vector<int> freq(n + 3, 0);
        for (long long x : ArrayToRearrange) {
            if (x <= n + 1) ++freq[(int)x];
        }

        if (mx <= n + 1) --freq[(int)mx];

        vector<char> present(n + 4, 0);
        if (mx <= n + 1) present[(int)mx] = 1;

        int mex = 0;
        while (present[mex]) ++mex;

        long long sum_mex = mex;

        for (int pos = 2; pos <= n; ++pos) {
            if (mex <= n + 1 && freq[mex] > 0) {
                --freq[mex];
                present[mex] = 1;
                while (present[mex]) ++mex;
            }
            sum_mex += mex;
        }

        cout << (sum_max + sum_mex) << '\n';
    }

    return 0;
}
