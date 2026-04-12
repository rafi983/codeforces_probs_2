#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

static vector<int> buildPrimes(int limit) {
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= limit; ++i) {
        if (!isPrime[i]) continue;
        for (int j = i * i; j <= limit; j += i) isPrime[j] = false;
    }
    vector<int> primes;
    for (int i = 2; i <= limit; ++i) if (isPrime[i]) primes.push_back(i);
    return primes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const vector<int> primes = buildPrimes(40000);

    // First 50 primes are enough as a guaranteed search pool for allowed multipliers.
    vector<int> firstPrimes;
    for (int p : primes) {
        firstPrimes.push_back(p);
        if ((int)firstPrimes.size() == 50) break;
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int64> a(n + 1), b(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) cin >> b[i];

        vector<int64> c(max(2, n), 0);
        for (int i = 1; i <= n - 1; ++i) c[i] = std::gcd(a[i], a[i + 1]);

        vector<int64> L(n + 1, 1);
        L[1] = c[1];
        L[n] = c[n - 1];
        for (int i = 2; i <= n - 1; ++i) {
            int64 g = std::gcd(c[i - 1], c[i]);
            L[i] = (c[i - 1] / g) * c[i];
        }

        auto lpfDistinct = [&](int64 x, unordered_set<int64>& out) {
            if (x <= 1) return;
            int64 y = x;
            for (int p : primes) {
                if (1LL * p * p > y) break;
                if (y % p == 0) {
                    out.insert(p);
                    while (y % p == 0) y /= p;
                }
            }
            if (y > 1) out.insert(y);
        };

        vector<int64> A(max(2, n), 1), B(n + 1, 1);

        for (int i = 1; i <= n - 1; ++i) {
            A[i] = L[i] / c[i];
            B[i + 1] = L[i + 1] / c[i];
        }

        vector<bool> variable(n + 1, false), fixedNode(n + 1, true);
        vector<int64> kFixed(n + 1, 1); // value = L[i] * k; for fixed nodes this k is fixed.

        int64 answer = 0;

        for (int i = 1; i <= n; ++i) {
            int64 Bi = b[i] / L[i];
            if (a[i] == L[i]) {
                if (Bi >= 2) {
                    variable[i] = true;     // can choose k=1 (unchanged) or prime k>1 (changed)
                    fixedNode[i] = false;
                } else {
                    // forced unchanged at k=1
                    fixedNode[i] = true;
                    kFixed[i] = 1;
                }
            } else {
                if (b[i] >= L[i]) {
                    // always optimal to set value to L[i] (changed, least restrictive).
                    answer++;
                    fixedNode[i] = true;
                    kFixed[i] = 1;
                } else {
                    // cannot change, must keep original value a[i] = L[i] * (a[i]/L[i]).
                    fixedNode[i] = true;
                    kFixed[i] = a[i] / L[i];
                }
            }
        }

        vector<vector<int64>> allowed(n + 1);

        for (int i = 1; i <= n; ++i) {
            if (!variable[i]) continue;

            int64 Bi = b[i] / L[i];
            unordered_set<int64> forbidden;

            if (i > 1) {
                lpfDistinct(A[i - 1], forbidden);
                if (fixedNode[i - 1]) lpfDistinct(kFixed[i - 1], forbidden);
            }
            if (i < n) {
                lpfDistinct(B[i + 1], forbidden);
                if (fixedNode[i + 1]) lpfDistinct(kFixed[i + 1], forbidden);
            }

            // Keep up to 3 allowed prime multipliers; 3 are sufficient on a path (degree <= 2).
            vector<int64> cand;
            for (int p : firstPrimes) {
                if (p > Bi) break;
                if (!forbidden.count(p)) {
                    cand.push_back(p);
                    if ((int)cand.size() == 3) break;
                }
            }
            allowed[i] = cand;
        }

        // DP per maximal consecutive segment of variable nodes.
        int i = 1;
        while (i <= n) {
            if (!variable[i]) {
                i++;
                continue;
            }
            int l = i;
            while (i <= n && variable[i]) i++;
            int r = i - 1;

            vector<pair<int64, int64>> dpPrev, dpCur;
            // state: (chosen prime multiplier; 0 means unchanged), best added ops in this segment so far.
            dpPrev.push_back({0, 0});

            for (int pos = l; pos <= r; ++pos) {
                vector<int64> states;
                states.push_back(0);
                for (int64 p : allowed[pos]) states.push_back(p);

                dpCur.clear();
                for (int64 curState : states) {
                    int64 best = LLONG_MIN / 4;
                    for (auto [prevState, prevVal] : dpPrev) {
                        if (curState != 0 && prevState != 0 && curState == prevState) continue;
                        best = max(best, prevVal + (curState != 0 ? 1 : 0));
                    }
                    dpCur.push_back({curState, best});
                }

                // compress duplicates of same state value.
                unordered_map<int64, int64> bestByState;
                for (auto [st, val] : dpCur) {
                    auto it = bestByState.find(st);
                    if (it == bestByState.end()) bestByState[st] = val;
                    else it->second = max(it->second, val);
                }
                dpPrev.clear();
                dpPrev.reserve(bestByState.size());
                for (auto &kv : bestByState) dpPrev.push_back({kv.first, kv.second});
            }

            int64 bestSeg = 0;
            for (auto [st, val] : dpPrev) bestSeg = max(bestSeg, val);
            answer += bestSeg;
        }

        cout << answer << '\n';
    }

    return 0;
}

