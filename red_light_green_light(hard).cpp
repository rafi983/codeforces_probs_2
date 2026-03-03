#include <bits/stdc++.h>
using namespace std;

static inline long long mod_norm(long long x, long long k) {
    x %= k;
    if (x < 0) x += k;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        long long k;
        cin >> n >> k;

        vector<long long> p(n), d(n);
        for (int i = 0; i < n; ++i) cin >> p[i];
        for (int i = 0; i < n; ++i) cin >> d[i];

        int q;
        cin >> q;
        vector<long long> a(q);
        for (int i = 0; i < q; ++i) cin >> a[i];

        vector<long long> c(n), s(n);
        c.reserve(n);
        s.reserve(n);

        for (int i = 0; i < n; ++i) {
            c[i] = mod_norm(d[i] - p[i], k);
            s[i] = mod_norm(d[i] + p[i], k);
        }

        unordered_map<long long, vector<int>> byC, byS;
        byC.reserve(static_cast<size_t>(n) * 2 + 7);
        byS.reserve(static_cast<size_t>(n) * 2 + 7);

        for (int i = 0; i < n; ++i) {
            byC[c[i]].push_back(i);
            byS[s[i]].push_back(i);
        }

        vector<int> nextSameC(n, -1), prevSameS(n, -1);

        for (auto &kv : byC) {
            auto &vec = kv.second;
            for (int i = 0; i + 1 < (int)vec.size(); ++i) {
                nextSameC[vec[i]] = vec[i + 1];
            }
        }

        for (auto &kv : byS) {
            auto &vec = kv.second;
            for (int i = 1; i < (int)vec.size(); ++i) {
                prevSameS[vec[i]] = vec[i - 1];
            }
        }

        const int NODES = 2 * n;
        vector<int> nxt(NODES, -1);

        for (int i = 0; i < n; ++i) {
            int jR = nextSameC[i];
            if (jR != -1) nxt[2 * i] = 2 * jR + 1;

            int jL = prevSameS[i];
            if (jL != -1) nxt[2 * i + 1] = 2 * jL;
        }

        vector<char> outcome(NODES, 0);

        for (int st = 0; st < NODES; ++st) {
            if (outcome[st] != 0) continue;

            vector<int> path;
            unordered_map<int, int> posInPath;
            posInPath.reserve(64);

            int u = st;
            bool exits = false;

            while (true) {
                if (u == -1) {
                    exits = true;
                    break;
                }
                if (outcome[u] == 2) {
                    exits = true;
                    break;
                }
                if (outcome[u] == 3) {
                    exits = false;
                    break;
                }
                auto it = posInPath.find(u);
                if (it != posInPath.end()) {
                    exits = false;
                    break;
                }

                posInPath[u] = static_cast<int>(path.size());
                path.push_back(u);
                u = nxt[u];
            }

            for (int v : path) {
                outcome[v] = exits ? 2 : 3;
            }
        }

        unordered_map<long long, int> posToIdx;
        posToIdx.reserve(static_cast<size_t>(n) * 2 + 7);
        for (int i = 0; i < n; ++i) posToIdx[p[i]] = i;

        for (int qi = 0; qi < q; ++qi) {
            long long start = a[qi];
            int startNode = -1;

            auto hit = posToIdx.find(start);
            bool immediateRed = false;
            int hitIdx = -1;
            if (hit != posToIdx.end()) {
                hitIdx = hit->second;
                immediateRed = (d[hitIdx] == 0);
            }

            if (immediateRed) {
                long long need = mod_norm(start, k);
                auto itList = byS.find(need);
                if (itList == byS.end()) {
                    startNode = -1;
                } else {
                    const auto &vec = itList->second;
                    auto it = lower_bound(vec.begin(), vec.end(), hitIdx);
                    if (it == vec.begin()) {
                        startNode = -1;
                    } else {
                        --it;
                        int j = *it;
                        startNode = 2 * j; // At j we turn to right.
                    }
                }
            } else {
                long long need = mod_norm(-start, k);
                int firstIdx = static_cast<int>(lower_bound(p.begin(), p.end(), start) - p.begin());

                auto itList = byC.find(need);
                if (itList == byC.end()) {
                    startNode = -1;
                } else {
                    const auto &vec = itList->second;
                    auto it = lower_bound(vec.begin(), vec.end(), firstIdx);
                    if (it == vec.end()) {
                        startNode = -1;
                    } else {
                        int j = *it;
                        startNode = 2 * j + 1; // At j we turn to left.
                    }
                }
            }

            bool ans = (startNode == -1) || (outcome[startNode] == 2);
            cout << (ans ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}

