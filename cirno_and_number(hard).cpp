#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

using i128 = __int128_t;

static i128 to_i128(const string &s) {
    i128 v = 0;
    for (char c : s) v = v * 10 + (c - '0');
    return v;
}

static void print_i128(i128 x) {
    if (x == 0) {
        cout << 0;
        return;
    }
    string s;
    while (x > 0) {
        s.push_back(char('0' + (x % 10)));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

static int get_min_digit(const vector<int> &d, bool nonzero_only) {
    for (int x : d) {
        if (!nonzero_only || x != 0) return x;
    }
    return -1;
}

static int get_max_digit(const vector<int> &d, bool nonzero_only) {
    for (int i = (int)d.size() - 1; i >= 0; --i) {
        if (!nonzero_only || d[i] != 0) return d[i];
    }
    return -1;
}

static int first_ge(const vector<int> &d, int x, bool nonzero_only) {
    for (int v : d) {
        if ((!nonzero_only || v != 0) && v >= x) return v;
    }
    return -1;
}

static int last_le(const vector<int> &d, int x, bool nonzero_only) {
    for (int i = (int)d.size() - 1; i >= 0; --i) {
        int v = d[i];
        if ((!nonzero_only || v != 0) && v <= x) return v;
    }
    return -1;
}

static string make_min_len(int len, const vector<int> &d) {
    if (len <= 0) return "";
    int first = get_min_digit(d, len > 1);
    if (first == -1) return "";

    int rest = get_min_digit(d, false);
    string s(len, char('0' + rest));
    s[0] = char('0' + first);
    return s;
}

static string make_max_len(int len, const vector<int> &d) {
    if (len <= 0) return "";
    int first = get_max_digit(d, len > 1);
    if (first == -1) return "";

    int rest = get_max_digit(d, false);
    string s(len, char('0' + rest));
    s[0] = char('0' + first);
    return s;
}

static string build_ge_same_len(const string &a, const vector<int> &d) {
    int n = (int)a.size();
    vector<int> pick(n, -1);

    for (int i = 0; i < n; ++i) {
        int need = a[i] - '0';
        int cur = first_ge(d, need, i == 0 && n > 1);

        if (cur != -1) {
            pick[i] = cur;
            if (cur > need) {
                int mn = get_min_digit(d, false);
                for (int j = i + 1; j < n; ++j) pick[j] = mn;
                string res(n, '0');
                for (int k = 0; k < n; ++k) res[k] = char('0' + pick[k]);
                return res;
            }
            continue;
        }

        for (int j = i - 1; j >= 0; --j) {
            int up = first_ge(d, pick[j] + 1, j == 0 && n > 1);
            if (up != -1) {
                pick[j] = up;
                int mn = get_min_digit(d, false);
                for (int k = j + 1; k < n; ++k) pick[k] = mn;
                string res(n, '0');
                for (int p = 0; p < n; ++p) res[p] = char('0' + pick[p]);
                return res;
            }
        }
        return "";
    }

    string res(n, '0');
    for (int i = 0; i < n; ++i) res[i] = char('0' + pick[i]);
    return res;
}

static string build_le_same_len(const string &a, const vector<int> &d) {
    int n = (int)a.size();
    vector<int> pick(n, -1);

    for (int i = 0; i < n; ++i) {
        int need = a[i] - '0';
        int cur = last_le(d, need, i == 0 && n > 1);

        if (cur != -1) {
            pick[i] = cur;
            if (cur < need) {
                int mx = get_max_digit(d, false);
                for (int j = i + 1; j < n; ++j) pick[j] = mx;
                string res(n, '0');
                for (int k = 0; k < n; ++k) res[k] = char('0' + pick[k]);
                return res;
            }
            continue;
        }

        for (int j = i - 1; j >= 0; --j) {
            int down = last_le(d, pick[j] - 1, j == 0 && n > 1);
            if (down != -1) {
                pick[j] = down;
                int mx = get_max_digit(d, false);
                for (int k = j + 1; k < n; ++k) pick[k] = mx;
                string res(n, '0');
                for (int p = 0; p < n; ++p) res[p] = char('0' + pick[p]);
                return res;
            }
        }
        return "";
    }

    string res(n, '0');
    for (int i = 0; i < n; ++i) res[i] = char('0' + pick[i]);
    return res;
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
        for (int i = 0; i < n; ++i) cin >> d[i];

        bool has_nonzero = false;
        for (int x : d) {
            if (x != 0) {
                has_nonzero = true;
                break;
            }
        }
        if (!has_nonzero) {
            cout << a << '\n';
            continue;
        }

        string s = to_string(a);
        vector<i128> cand;

        string x = build_ge_same_len(s, d);
        if (!x.empty()) cand.push_back(to_i128(x));

        x = build_le_same_len(s, d);
        if (!x.empty()) cand.push_back(to_i128(x));

        x = make_min_len((int)s.size() + 1, d);
        if (!x.empty()) cand.push_back(to_i128(x));

        if (s.size() > 1) {
            x = make_max_len((int)s.size() - 1, d);
            if (!x.empty()) cand.push_back(to_i128(x));
        }

        i128 A = (i128)a;
        i128 ans = -1;
        for (i128 v : cand) {
            i128 diff = (A >= v ? A - v : v - A);
            if (ans == -1 || diff < ans) ans = diff;
        }

        print_i128(ans);
        cout << '\n';
    }

    return 0;
}
