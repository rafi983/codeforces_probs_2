#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

static const int MAXV = 1000000;
static const int INF = 1000000000;

static vector<int> build_spf() {
    vector<int> spf(MAXV + 1);
    for (int i = 0; i <= MAXV; ++i) spf[i] = i;
    for (int i = 2; i * i <= MAXV; ++i) {
        if (spf[i] != i) continue;
        for (int j = i * i; j <= MAXV; j += i) {
            if (spf[j] == j) spf[j] = i;
        }
    }
    return spf;
}

static vector<pair<int, int>> factorize(int n, const vector<int>& spf) {
    vector<pair<int, int>> f;
    while (n > 1) {
        int p = spf[n];
        int c = 0;
        while (n % p == 0) {
            n /= p;
            ++c;
        }
        f.push_back({p, c});
    }
    return f;
}

static void gen_divisors_dfs(
    int idx,
    long long cur,
    const vector<pair<int, int>>& fac,
    vector<int>& divisors
) {
    if (idx == (int)fac.size()) {
        divisors.push_back((int)cur);
        return;
    }

    auto [p, cnt] = fac[idx];
    long long v = 1;
    for (int e = 0; e <= cnt; ++e) {
        gen_divisors_dfs(idx + 1, cur * v, fac, divisors);
        v *= p;
    }
}

static int min_ops_for_ratio(int n, int k, const vector<int>& spf) {
    if (n == 1) return 0;
    if (k == 1) return -1;

    vector<pair<int, int>> fac = factorize(n, spf);
    vector<int> all_divs;
    gen_divisors_dfs(0, 1, fac, all_divs);

    vector<int> cand;
    cand.reserve(all_divs.size());
    for (int d : all_divs) {
        if (d >= 2 && d <= k) cand.push_back(d);
    }
    if (cand.empty()) return -1;

    sort(all_divs.begin(), all_divs.end());
    vector<int> states = all_divs;
    vector<int> dp(states.size(), INF);

    dp[0] = 0;

    for (int i = 1; i < (int)states.size(); ++i) {
        int m = states[i];
        int best = INF;
        for (int d : cand) {
            if (d > m) continue;
            if (m % d != 0) continue;
            int prev = m / d;
            int pos = (int)(lower_bound(states.begin(), states.end(), prev) - states.begin());
            if (pos < (int)states.size() && states[pos] == prev && dp[pos] != INF) {
                best = min(best, dp[pos] + 1);
            }
        }
        dp[i] = best;
    }

    int ans = dp.back();
    return ans == INF ? -1 : ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> spf = build_spf();

    int t;
    cin >> t;
    while (t--) {
        int x, y, k;
        cin >> x >> y >> k;

        int g = gcd(x, y);
        int need_div = x / g;
        int need_mul = y / g;

        int a = min_ops_for_ratio(need_div, k, spf);
        int b = min_ops_for_ratio(need_mul, k, spf);

        if (a == -1 || b == -1) {
            cout << -1 << '\n';
        } else {
            cout << (a + b) << '\n';
        }
    }

    return 0;
}

