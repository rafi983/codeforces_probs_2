#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = (ll)1e15;
map<pair<vector<ll>, int>, tuple<ll, ll, ll>> memo;

// minimal worst-case total loss to identify x in S with k rounds left; returns (cost, a, b) in absolute coordinates
tuple<ll, ll, ll> solve(const vector<ll> &S, int k) {
    if (S.size() == 1) return {0, S[0], S[0]};
    if (k == 0) return {INF, 0, 0};
    vector<ll> norm(S.size());
    for (size_t i = 0; i < S.size(); ++i) norm[i] = S[i] - S[0];
    auto key = make_pair(norm, k);
    auto it = memo.find(key);
    if (it != memo.end()) {
        auto [c, a, b] = it->second;
        return {c, a + S[0], b + S[0]};
    }
    set<ll> menu;
    int m = S.size();
    for (int i = 0; i < m; ++i) {
        for (int dl = -2; dl <= 2; ++dl) menu.insert(S[i] + dl);
        for (int j = i + 1; j < m; ++j) {
            ll mid = (S[i] + S[j]) / 2;
            for (int dl = -1; dl <= 1; ++dl) menu.insert(mid + dl);
        }
    }
    vector<ll> pts(menu.begin(), menu.end());
    ll best = INF, ba = 0, bb = 0;
    for (size_t i = 0; i < pts.size(); ++i)
        for (size_t j = i; j < pts.size(); ++j) {
            ll a = pts[i], b = pts[j];
            map<ll, vector<ll>> g;
            for (ll x : S) g[min(llabs(x - a), llabs(x - b))].push_back(x);
            if (g.size() == 1) continue;
            ll w = 0;
            for (auto &[d, l] : g) {
                w = max(w, d + get<0>(solve(l, k - 1)));
                if (w >= best) break;
            }
            if (w < best) { best = w; ba = a; bb = b; }
        }
    memo[key] = {best, ba - S[0], bb - S[0]};
    return {best, ba, bb};
}

const ll N = 10000, A1 = 1428, B1 = 7142;

vector<ll> firstCandidates(ll d) {
    vector<ll> c;
    for (ll x : {A1 - d, A1 + d, B1 - d, B1 + d})
        if (x >= 1 && x <= N && min(llabs(x - A1), llabs(x - B1)) == d) c.push_back(x);
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
    return c;
}

#ifdef SIM
int main() {
    ll worst = 0;
    for (ll x = 1; x <= N; ++x) {
        ll d = min(llabs(x - A1), llabs(x - B1));
        ll tot = d;
        vector<ll> S = firstCandidates(d);
        int k = 9;
        while (k > 0) {
            if (S.size() == 1) break;
            auto [c, a, b] = solve(S, k);
            if (c >= INF) { printf("FAIL x=%lld\n", x); return 1; }
            ll dd = min(llabs(x - a), llabs(x - b));
            tot += dd;
            vector<ll> T;
            for (ll y : S) if (min(llabs(y - a), llabs(y - b)) == dd) T.push_back(y);
            S = T;
            --k;
        }
        if (worst < tot) { worst = tot; printf("x=%lld total=%lld\n", x, tot); }
    }
    printf("worst %lld\n", worst);
}
#else
int main() {
    int t;
    cin >> t;
    while (t--) {
        cout << A1 << ' ' << B1 << endl;
        ll d;
        cin >> d;
        vector<ll> S = firstCandidates(d);
        for (int k = 9; k >= 1; --k) {
            ll a, b;
            if (S.size() == 1) { a = b = S[0]; }
            else { auto [c, qa, qb] = solve(S, k); a = qa; b = qb; }
            cout << a << ' ' << b << endl;
            cin >> d;
            vector<ll> T;
            for (ll y : S) if (min(llabs(y - a), llabs(y - b)) == d) T.push_back(y);
            S = T;
        }
    }
    return 0;
}
#endif

