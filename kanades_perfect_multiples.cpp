#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static vector<int> build_primes(int limit) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= limit; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (is_prime[i]) primes.push_back(i);
    }
    return primes;
}

static vector<pair<int, int>> factorize(int x, const vector<int>& primes) {
    vector<pair<int, int>> fac;
    for (int p : primes) {
        if (1LL * p * p > x) break;
        if (x % p == 0) {
            int cnt = 0;
            while (x % p == 0) {
                x /= p;
                ++cnt;
            }
            fac.push_back({p, cnt});
        }
    }
    if (x > 1) fac.push_back({x, 1});
    return fac;
}

static void gen_divisors_dfs(int idx, int cur, const vector<pair<int, int>>& fac, vector<int>& out) {
    if (idx == (int)fac.size()) {
        out.push_back(cur);
        return;
    }
    int p = fac[idx].first;
    int e = fac[idx].second;
    int val = cur;
    for (int i = 0; i <= e; ++i) {
        gen_divisors_dfs(idx + 1, val, fac, out);
        if (i < e) val *= p;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const vector<int> primes = build_primes(31623);

    int t;
    cin >> t;
    while (t--) {
        int n;
        ll k;
        cin >> n >> k;

        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        int m = (int)a.size();

        unordered_map<int, int> id;
        id.reserve(m * 2 + 1);
        id.max_load_factor(0.7f);
        for (int i = 0; i < m; ++i) {
            id[a[i]] = i;
        }

        vector<vector<int>> divisors(m);
        vector<int> multiple_count(m, 0);

        for (int i = 0; i < m; ++i) {
            auto fac = factorize(a[i], primes);
            vector<int> all_divs;
            all_divs.reserve(64);
            gen_divisors_dfs(0, 1, fac, all_divs);
            sort(all_divs.begin(), all_divs.end());

            for (int d : all_divs) {
                auto it = id.find(d);
                if (it != id.end()) {
                    divisors[i].push_back(d);
                    ++multiple_count[it->second];
                }
            }
        }

        vector<char> good(m, false);
        for (int i = 0; i < m; ++i) {
            if ((ll)multiple_count[i] == k / a[i]) {
                good[i] = true;
            }
        }

        vector<int> answer;
        answer.reserve(m);
        bool ok = true;

        for (int i = 0; i < m; ++i) {
            bool covered = false;
            bool minimal_good = good[i];

            for (int d : divisors[i]) {
                int idx = id[d];
                if (good[idx]) {
                    covered = true;
                    if (d != a[i]) {
                        minimal_good = false;
                    }
                }
            }

            if (!covered) {
                ok = false;
                break;
            }
            if (minimal_good) {
                answer.push_back(a[i]);
            }
        }

        if (!ok) {
            cout << -1 << '\n';
            continue;
        }

        cout << answer.size() << '\n';
        for (int i = 0; i < (int)answer.size(); ++i) {
            if (i) cout << ' ';
            cout << answer[i];
        }
        cout << '\n';
    }

    return 0;
}

