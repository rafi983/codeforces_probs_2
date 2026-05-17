#include <iostream>
#include <vector>
using namespace std;

static const long long MOD = 998244353;

static long long mod_pow(long long a, long long e) {
    long long r = 1;
    while (e > 0) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

static vector<long long> fact(1, 1), invfact(1, 1);

static void ensure_fact(int n) {
    int cur = (int)fact.size() - 1;
    if (cur >= n) return;

    fact.resize(n + 1);
    for (int i = cur + 1; i <= n; ++i) fact[i] = fact[i - 1] * i % MOD;

    invfact.resize(n + 1);
    invfact[n] = mod_pow(fact[n], MOD - 2);
    for (int i = n; i > cur; --i) invfact[i - 1] = invfact[i] * i % MOD;
}

static long long C(long long n, long long r) {
    if (r < 0 || r > n) return 0;
    ensure_fact((int)n);
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}

struct Node {
    int len;
    int k;
    long long s_exact;

    long long sum_u;
    long long sum_u2p;
    long long sum_F;
    long long sum_F2;
    long long sum_Fu;

    Node()
        : len(0), k(0), s_exact(0), sum_u(0), sum_u2p(0), sum_F(0), sum_F2(0), sum_Fu(0) {}
};

static Node merge_node(const Node &L, const Node &R) {
    if (L.len == 0) return R;
    if (R.len == 0) return L;

    Node res;
    res.len = L.len + R.len;
    res.k = L.k + R.k;
    res.s_exact = L.s_exact + R.s_exact;

    long long lenR = R.len % MOD;
    long long kL = L.k % MOD;
    long long sL = L.s_exact % MOD;

    res.sum_u = (L.sum_u + R.sum_u + lenR * kL) % MOD;

    long long term_u2 = R.sum_u2p;
    term_u2 = (term_u2 + 2LL * kL % MOD * R.sum_u) % MOD;
    term_u2 = (term_u2 + lenR * (kL * ((kL + 1) % MOD) % MOD)) % MOD;
    res.sum_u2p = (L.sum_u2p + term_u2) % MOD;

    long long term_F = (R.sum_F + lenR * sL) % MOD;
    res.sum_F = (L.sum_F + term_F) % MOD;

    long long term_F2 = R.sum_F2;
    term_F2 = (term_F2 + 2LL * sL % MOD * R.sum_F) % MOD;
    term_F2 = (term_F2 + lenR * (sL * sL % MOD)) % MOD;
    res.sum_F2 = (L.sum_F2 + term_F2) % MOD;

    long long term_Fu = R.sum_Fu;
    term_Fu = (term_Fu + sL * R.sum_u) % MOD;
    term_Fu = (term_Fu + kL * R.sum_F) % MOD;
    term_Fu = (term_Fu + lenR * (sL * kL % MOD)) % MOD;
    res.sum_Fu = (L.sum_Fu + term_Fu) % MOD;

    return res;
}

static Node make_leaf(int v) {
    Node x;
    x.len = 1;
    if (v == -1) {
        x.k = 1;
        x.s_exact = 0;
        x.sum_u = 1;
        x.sum_u2p = 2;
        x.sum_F = 0;
        x.sum_F2 = 0;
        x.sum_Fu = 0;
    } else {
        long long vm = v % MOD;
        x.k = 0;
        x.s_exact = v;
        x.sum_u = 0;
        x.sum_u2p = 0;
        x.sum_F = vm;
        x.sum_F2 = vm * vm % MOD;
        x.sum_Fu = 0;
    }
    return x;
}

struct SegTree {
    int n;
    vector<Node> st;

    explicit SegTree(const vector<int> &a) {
        n = (int)a.size() - 1;
        st.assign(4 * n + 5, Node());
        build(1, 1, n, a);
    }

    void build(int p, int l, int r, const vector<int> &a) {
        if (l == r) {
            st[p] = make_leaf(a[l]);
            return;
        }
        int m = (l + r) >> 1;
        build(p << 1, l, m, a);
        build(p << 1 | 1, m + 1, r, a);
        st[p] = merge_node(st[p << 1], st[p << 1 | 1]);
    }

    void update(int p, int l, int r, int idx, int val) {
        if (l == r) {
            st[p] = make_leaf(val);
            return;
        }
        int m = (l + r) >> 1;
        if (idx <= m) update(p << 1, l, m, idx, val);
        else update(p << 1 | 1, m + 1, r, idx, val);
        st[p] = merge_node(st[p << 1], st[p << 1 | 1]);
    }

    Node query(int p, int l, int r, int ql, int qr) const {
        if (ql <= l && r <= qr) return st[p];
        int m = (l + r) >> 1;
        if (qr <= m) return query(p << 1, l, m, ql, qr);
        if (ql > m) return query(p << 1 | 1, m + 1, r, ql, qr);
        Node left = query(p << 1, l, m, ql, qr);
        Node right = query(p << 1 | 1, m + 1, r, ql, qr);
        return merge_node(left, right);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];

        SegTree seg(a);

        while (q--) {
            int op;
            cin >> op;
            if (op == 1) {
                int p, v;
                cin >> p >> v;
                seg.update(1, 1, n, p, v);
            } else {
                int l, r;
                long long m;
                cin >> l >> r >> m;

                Node nd = seg.query(1, 1, n, l, r);
                long long R = m - nd.s_exact;
                if (R < 0) {
                    cout << 0 << '\n';
                    continue;
                }

                if (nd.k == 0) {
                    if (R != 0) cout << 0 << '\n';
                    else cout << nd.sum_F2 % MOD << '\n';
                    continue;
                }

                long long N = C(R + nd.k - 1, nd.k - 1);
                long long B = C(R + nd.k - 1, nd.k);
                long long A = C(R + nd.k - 1, nd.k + 1);

                long long ans = 0;
                ans = (ans + N * nd.sum_F2) % MOD;
                ans = (ans + 2LL * B % MOD * nd.sum_Fu) % MOD;
                ans = (ans + A * nd.sum_u2p) % MOD;
                ans = (ans + B * nd.sum_u) % MOD;

                cout << ans << '\n';
            }
        }
    }

    return 0;
}
