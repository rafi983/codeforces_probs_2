#include <bits/stdc++.h>
using namespace std;

static const int MOD = 998244353;
static const int MAXN = 1000005;

long long mod_pow(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e > 0) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

vector<int> manacher_even(const vector<int>& s) {
    int n = (int)s.size();
    vector<int> d2(n, 0);
    int l = 0, r = -1;
    for (int i = 0; i < n; ++i) {
        int k = (i > r ? 0 : min(d2[l + r - i + 1], r - i + 1));
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) ++k;
        d2[i] = k;
        if (i + k - 1 > r) {
            l = i - k;
            r = i + k - 1;
        }
    }
    return d2;
}

struct Node {
    int cnt = 0;
    vector<int> child;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    static vector<long long> fact(MAXN, 1);
    static bool inited = false;
    if (!inited) {
        for (int i = 1; i < MAXN; ++i) fact[i] = fact[i - 1] * i % MOD;
        inited = true;
    }

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        vector<int> d2 = manacher_even(a);
        long long base = 0;
        for (int x : d2) base += x;

        vector<int> nxt(n), last(m + 1, n);
        for (int i = n - 1; i >= 0; --i) {
            nxt[i] = last[a[i]];
            last[a[i]] = i;
        }

        vector<Node> trie;
        trie.reserve(2 * n + 5);
        trie.push_back(Node());

        unordered_map<long long, int> edge;
        edge.reserve(4 * n + 20);
        edge.max_load_factor(0.7f);

        auto key_of = [&](int u, int val) -> long long {
            return ((long long)u << 21) ^ (long long)val;
        };

        auto add_path = [&](const vector<int>& seq) {
            int u = 0;
            trie[u].cnt++;
            for (int x : seq) {
                long long key = key_of(u, x);
                auto it = edge.find(key);
                if (it == edge.end()) {
                    int v = (int)trie.size();
                    trie.push_back(Node());
                    edge[key] = v;
                    trie[u].child.push_back(v);
                    u = v;
                } else {
                    u = it->second;
                }
                trie[u].cnt++;
            }
        };

        for (int center = 1; center < n; ++center) {
            int need = n - center;
            if (d2[center] < need) continue;

            int left_end = 2 * center - n - 1;
            vector<int> seq;
            for (int j = left_end; j >= 0; --j) {
                if (nxt[j] <= left_end) break;
                seq.push_back(a[j]);
            }
            add_path(seq);
        }

        {
            vector<int> seq;
            for (int j = n - 1; j >= 0; --j) {
                if (nxt[j] < n) break;
                seq.push_back(a[j]);
            }
            add_path(seq);
        }

        unordered_map<int, long long> ways_by_total;
        ways_by_total.reserve(2 * (int)trie.size() + 10);
        ways_by_total.max_load_factor(0.7f);

        function<void(int, int, int)> dfs = [&](int u, int sum, int rem) {
            if (rem == 0) {
                ways_by_total[sum] = (ways_by_total[sum] + 1) % MOD;
                return;
            }

            int c = (int)trie[u].child.size();
            long long leave_now = (long long)(rem - c) * fact[rem - 1] % MOD;
            ways_by_total[sum] = (ways_by_total[sum] + leave_now) % MOD;

            for (int v : trie[u].child) {
                dfs(v, sum + trie[v].cnt, rem - 1);
            }
        };

        dfs(0, (int)base, m);

        long long ans = 0;
        for (auto& kv : ways_by_total) {
            int total_pal = kv.first;
            long long cnt_perm = kv.second % MOD;
            ans = (ans + mod_pow(cnt_perm, total_pal + 1)) % MOD;
        }

        cout << ans << '\n';
    }

    return 0;
}
