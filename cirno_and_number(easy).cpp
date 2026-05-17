#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

static long long to_ll(const string &s) {
    long long v = 0;
    for (char c : s) v = v * 10 + (c - '0');
    return v;
}

static int get_min(const vector<int> &d, bool no_zero) {
    for (int x : d) if (!no_zero || x != 0) return x;
    return -1;
}

static int get_max(const vector<int> &d, bool no_zero) {
    for (int i = (int)d.size() - 1; i >= 0; --i) {
        if (!no_zero || d[i] != 0) return d[i];
    }
    return -1;
}

static int first_ge(const vector<int> &d, int x, bool no_zero) {
    for (int v : d) if ((!no_zero || v != 0) && v >= x) return v;
    return -1;
}

static int last_le(const vector<int> &d, int x, bool no_zero) {
    for (int i = (int)d.size() - 1; i >= 0; --i) {
        int v = d[i];
        if ((!no_zero || v != 0) && v <= x) return v;
    }
    return -1;
}

static string make_min_len(int len, const vector<int> &d) {
    if (len <= 0) return "";
    string s(len, '0');
    s[0] = char('0' + get_min(d, len > 1));
    for (int i = 1; i < len; ++i) s[i] = char('0' + get_min(d, false));
    return s;
}

static string make_max_len(int len, const vector<int> &d) {
    if (len <= 0) return "";
    string s(len, '0');
    s[0] = char('0' + get_max(d, len > 1));
    for (int i = 1; i < len; ++i) s[i] = char('0' + get_max(d, false));
    return s;
}

static string build_ge(const string &a, const vector<int> &d) {
    int n = (int)a.size();
    vector<int> p(n, -1);

    for (int i = 0; i < n; ++i) {
        int need = a[i] - '0';
        int pick = first_ge(d, need, i == 0 && n > 1);
        if (pick != -1) {
            p[i] = pick;
            if (pick > need) {
                int mn = get_min(d, false);
                for (int j = i + 1; j < n; ++j) p[j] = mn;
                string r(n, '0');
                for (int j = 0; j < n; ++j) r[j] = char('0' + p[j]);
                return r;
            }
            continue;
        }

        for (int j = i - 1; j >= 0; --j) {
            int up = first_ge(d, p[j] + 1, j == 0 && n > 1);
            if (up != -1) {
                p[j] = up;
                int mn = get_min(d, false);
                for (int k = j + 1; k < n; ++k) p[k] = mn;
                string r(n, '0');
                for (int k = 0; k < n; ++k) r[k] = char('0' + p[k]);
                return r;
            }
        }
        return "";
    }

    string r(n, '0');
    for (int i = 0; i < n; ++i) r[i] = char('0' + p[i]);
    return r;
}

static string build_le(const string &a, const vector<int> &d) {
    int n = (int)a.size();
    vector<int> p(n, -1);

    for (int i = 0; i < n; ++i) {
        int need = a[i] - '0';
        int pick = last_le(d, need, i == 0 && n > 1);
        if (pick != -1) {
            p[i] = pick;
            if (pick < need) {
                int mx = get_max(d, false);
                for (int j = i + 1; j < n; ++j) p[j] = mx;
                string r(n, '0');
                for (int j = 0; j < n; ++j) r[j] = char('0' + p[j]);
                return r;
            }
            continue;
        }

        for (int j = i - 1; j >= 0; --j) {
            int down = last_le(d, p[j] - 1, j == 0 && n > 1);
            if (down != -1) {
                p[j] = down;
                int mx = get_max(d, false);
                for (int k = j + 1; k < n; ++k) p[k] = mx;
                string r(n, '0');
                for (int k = 0; k < n; ++k) r[k] = char('0' + p[k]);
                return r;
            }
        }
        return "";
    }

    string r(n, '0');
    for (int i = 0; i < n; ++i) r[i] = char('0' + p[i]);
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long a;
        int n;
        cin >> a >> n;

        vector<int> d(n);
        cin >> d[0] >> d[1];
        sort(d.begin(), d.end());

        string s = to_string(a);
        vector<long long> c;

        string x = build_ge(s, d);
        if (!x.empty()) c.push_back(to_ll(x));

        x = build_le(s, d);
        if (!x.empty()) c.push_back(to_ll(x));

        x = make_min_len((int)s.size() + 1, d);
        if (!x.empty()) c.push_back(to_ll(x));

        if (s.size() > 1) {
            x = make_max_len((int)s.size() - 1, d);
            if (!x.empty()) c.push_back(to_ll(x));
        }

        long long ans = (1LL << 62);
        for (long long v : c) ans = min(ans, llabs(a - v));
        cout << ans << '\n';
    }

    return 0;
}
