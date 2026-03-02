#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 0;
    if (!(cin >> t)) {
        return 0;
    }

    const long long NEG = -1000000000000000000LL;

    while (t--) {
        int n = 0;
        long long k = 0;
        cin >> n >> k;

        string s;
        cin >> s;

        vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        vector<long long> leftEnd(n, 0);
        vector<long long> rightStart(n, 0);

        long long maxKnown = LLONG_MIN;
        long long cur = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') {
                cur = max(a[i], cur + a[i]);
                maxKnown = max(maxKnown, cur);
            } else {
                cur = 0;
            }
        }

        if (maxKnown > k) {
            cout << "No\n";
            continue;
        }

        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') {
                if (i == 0 || s[i - 1] == '0') {
                    leftEnd[i] = a[i];
                } else {
                    leftEnd[i] = max(a[i], a[i] + leftEnd[i - 1]);
                }
            } else {
                leftEnd[i] = 0;
            }
        }

        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == '1') {
                if (i == n - 1 || s[i + 1] == '0') {
                    rightStart[i] = a[i];
                } else {
                    rightStart[i] = max(a[i], a[i] + rightStart[i + 1]);
                }
            } else {
                rightStart[i] = 0;
            }
        }

        bool hasZero = (s.find('0') != string::npos);
        if (!hasZero) {
            if (maxKnown == k) {
                cout << "Yes\n";
                for (int i = 0; i < n; ++i) {
                    if (i) cout << ' ';
                    cout << a[i];
                }
                cout << "\n";
            } else {
                cout << "No\n";
            }
            continue;
        }

        vector<long long> ans = a;

        if (maxKnown == k) {
            for (int i = 0; i < n; ++i) {
                if (s[i] == '0') {
                    ans[i] = NEG;
                }
            }
            cout << "Yes\n";
            for (int i = 0; i < n; ++i) {
                if (i) cout << ' ';
                cout << ans[i];
            }
            cout << "\n";
            continue;
        }

        int pos = -1;
        long long leftMax = 0;
        long long rightMax = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') {
                pos = i;
                if (i > 0) leftMax = max(0LL, leftEnd[i - 1]);
                if (i + 1 < n) rightMax = max(0LL, rightStart[i + 1]);
                break;
            }
        }

        long long x = k - leftMax - rightMax;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') {
                ans[i] = NEG;
            }
        }
        if (pos != -1) {
            ans[pos] = x;
        }

        cout << "Yes\n";
        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << "\n";
    }

    return 0;
}
