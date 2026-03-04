#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        long long mod;
        cin >> n >> k >> mod;

        vector<long long> F(k + 1, 0), D(k + 1, 0);
        vector<long long> nF(k + 1, 0), nD(k + 1, 0);

        for (int m = 0; m <= k; ++m) {
            F[m] = 1;
            D[m] = 1;
        }

        for (int h = 2; h <= n; ++h) {
            fill(nF.begin(), nF.end(), 0);
            fill(nD.begin(), nD.end(), 0);

            vector<long long> convF(k + 1, 0), prefConvF(k + 1, 0);
            for (int x = 0; x <= k; ++x) {
                if (F[x] == 0) continue;
                for (int y = 0; x + y <= k; ++y) {
                    if (F[y] == 0) continue;
                    convF[x + y] = (convF[x + y] + F[x] * F[y]) % mod;
                }
            }
            prefConvF[0] = convF[0] % mod;
            for (int m = 1; m <= k; ++m) {
                prefConvF[m] = (prefConvF[m - 1] + convF[m]) % mod;
            }
            for (int m = 0; m <= k; ++m) {
                nF[m] = prefConvF[m];
            }

            vector<long long> baseDet(k + 1, 0), prefDet(k + 1, 0);
            for (int x = 0; x <= k; ++x) {
                for (int y = 0; x + y <= k; ++y) {
                    if (x == y) continue;
                    long long ways = 0;
                    if (x > y) {
                        ways = (D[x] * F[y]) % mod;
                    } else {
                        ways = (F[x] * D[y]) % mod;
                    }
                    baseDet[x + y] += ways;
                    if (baseDet[x + y] >= mod) baseDet[x + y] -= mod;
                }
            }
            prefDet[0] = baseDet[0] % mod;
            for (int m = 1; m <= k; ++m) {
                prefDet[m] = (prefDet[m - 1] + baseDet[m]) % mod;
            }
            for (int m = 0; m <= k; ++m) {
                nD[m] = prefDet[m];
            }

            F.swap(nF);
            D.swap(nD);
        }

        cout << (D[k] % mod) << '\n';
    }

    return 0;
}

