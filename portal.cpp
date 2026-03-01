#include <bits/stdc++.h>
using namespace std;

static int booth_min_rotation_start(const vector<int>& a) {
    int n = static_cast<int>(a.size());
    if (n == 0) {
        return 0;
    }
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        int x = a[(i + k) % n];
        int y = a[(j + k) % n];
        if (x == y) {
            ++k;
        } else if (x < y) {
            j = j + k + 1;
            if (j == i) {
                ++j;
            }
            k = 0;
        } else {
            i = i + k + 1;
            if (i == j) {
                ++i;
            }
            k = 0;
        }
    }
    return min(i, j);
}

static vector<int> min_rotation(const vector<int>& a) {
    int n = static_cast<int>(a.size());
    if (n == 0) {
        return {};
    }
    int start = booth_min_rotation_start(a);
    vector<int> res;
    res.reserve(n);
    for (int i = 0; i < n; ++i) {
        res.push_back(a[(start + i) % n]);
    }
    return res;
}

static vector<int> z_algorithm(const vector<int>& s) {
    int n = static_cast<int>(s.size());
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

static vector<int> solve_one(int n, int x, int y, const vector<int>& p) {
    vector<int> left(p.begin(), p.begin() + x);
    vector<int> middle(p.begin() + x, p.begin() + y);
    vector<int> right(p.begin() + y, p.end());

    vector<int> c;
    c.reserve(n - static_cast<int>(middle.size()));
    c.insert(c.end(), left.begin(), left.end());
    c.insert(c.end(), right.begin(), right.end());

    if (middle.empty()) {
        return c;
    }

    vector<int> b = min_rotation(middle);
    if (c.empty()) {
        return b;
    }

    vector<int> t;
    t.reserve(b.size() + 1 + c.size());
    t.insert(t.end(), b.begin(), b.end());
    t.push_back(0);
    t.insert(t.end(), c.begin(), c.end());

    vector<int> z = z_algorithm(t);

    int m = static_cast<int>(b.size());
    int c_len = static_cast<int>(c.size());
    int best_k = c_len;

    for (int k = 0; k < c_len; ++k) {
        int lcp = z[m + 1 + k];
        if (lcp == m) {
            if (m < c_len - k) {
                best_k = k;
                break;
            }
        } else if (lcp == c_len - k) {
            continue;
        } else {
            if (b[lcp] < c[k + lcp]) {
                best_k = k;
                break;
            }
        }
    }

    vector<int> res;
    res.reserve(n);
    res.insert(res.end(), c.begin(), c.begin() + best_k);
    res.insert(res.end(), b.begin(), b.end());
    res.insert(res.end(), c.begin() + best_k, c.end());
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 0;
    if (!(cin >> t)) {
        return 0;
    }
    while (t--) {
        int n = 0, x = 0, y = 0;
        cin >> n >> x >> y;
        vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i];
        }
        vector<int> ans = solve_one(n, x, y, p);
        for (int i = 0; i < n; ++i) {
            if (i) {
                cout << ' ';
            }
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}

