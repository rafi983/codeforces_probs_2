#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXV = 1'000'000;
    vector<int> globalFreq(MAXV + 1, 0);
    vector<int> touched;
    touched.reserve(200000);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        long long totalLen = 0;
        long long mexSum = 0;
        long long sourceDeltaSum = 0;

        vector<int> mex(n), inc(n);

        for (int i = 0; i < n; ++i) {
            int len;
            cin >> len;
            totalLen += len;

            vector<int> cnt(len + 2, 0);

            for (int j = 0; j < len; ++j) {
                int v;
                cin >> v;

                if (globalFreq[v] == 0) touched.push_back(v);
                ++globalFreq[v];

                if (v <= len + 1) ++cnt[v];
            }

            int m = 0;
            while (m <= len + 1 && cnt[m] > 0) ++m;
            mex[i] = m;
            mexSum += m;

            long long localSrc = 0;
            for (int x = 0; x < m; ++x) {
                if (cnt[x] == 1) localSrc += (long long)x - m;
            }
            sourceDeltaSum += localSrc;

            int nxt = m + 1;
            while (nxt <= len + 1 && cnt[nxt] > 0) ++nxt;
            inc[i] = nxt - m;
        }

        long long operations = totalLen * (n - 1LL);
        long long ans = mexSum * operations;

        ans += (n - 1LL) * sourceDeltaSum;

        long long targetDelta = 0;
        for (int i = 0; i < n; ++i) {
            targetDelta += 1LL * inc[i] * globalFreq[mex[i]];
        }
        ans += targetDelta;

        cout << ans << '\n';

        for (int v : touched) globalFreq[v] = 0;
        touched.clear();
    }

    return 0;
}

