#include <bits/stdc++.h>
using namespace std;

static int countUgly(const vector<int>& a) {
    int n = static_cast<int>(a.size());
    int maxv = 0;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        maxv = max(maxv, a[i]);
        if (maxv <= i + 1) {
            ++cnt;
        }
    }
    return cnt;
}

static vector<int> minimizeUgly(vector<int> p) {
    int n = static_cast<int>(p.size());
    vector<int> prefMax(n);
    vector<int> ugly(n);
    int maxv = 0;
    int totalUgly = 0;
    for (int i = 0; i < n; ++i) {
        maxv = max(maxv, p[i]);
        prefMax[i] = maxv;
        ugly[i] = (prefMax[i] == i + 1) ? 1 : 0;
        totalUgly += ugly[i];
    }

    int bestCount = totalUgly;
    vector<int> best = p;

    for (int x = 0; x < n; ++x) {
        for (int y = x + 1; y < n; ++y) {
            int current = totalUgly;
            int prev = (x == 0) ? 0 : prefMax[x - 1];
            for (int i = x; i < y; ++i) {
                int val = (i == x) ? p[y] : p[i];
                prev = max(prev, val);
                int newUgly = (prev == i + 1) ? 1 : 0;
                if (newUgly != ugly[i]) {
                    current += (newUgly - ugly[i]);
                }
            }

            if (current < bestCount) {
                bestCount = current;
                best = p;
                swap(best[x], best[y]);
                if (bestCount == 0) {
                    return best;
                }
            }
        }
    }
    return best;
}

static void solve(istream& in, ostream& out) {
    int t = 0;
    in >> t;
    while (t--) {
        int n = 0;
        in >> n;
        vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            in >> p[i];
        }
        vector<int> q = minimizeUgly(p);
        for (int i = 0; i < n; ++i) {
            if (i) out << ' ';
            out << q[i];
        }
        out << '\n';
    }
}

#ifndef UNIT_TEST
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve(cin, cout);
    return 0;
}
#endif
