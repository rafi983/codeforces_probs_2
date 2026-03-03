#include <bits/stdc++.h>
using namespace std;

static inline int dir_bit(int dir) {
    return dir == 1 ? 1 : 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<long long> p(n);
        vector<int> d(n);
        for (int i = 0; i < n; ++i) cin >> p[i];
        for (int i = 0; i < n; ++i) cin >> d[i];

        int q;
        cin >> q;
        vector<long long> a(q);
        for (int i = 0; i < q; ++i) cin >> a[i];

        auto id = [k](int i, int tm, int dbit) {
            return ((i * k + tm) << 1) | dbit;
        };

        const int S = n * k * 2;
        vector<int> nxt(S, -1);

        for (int i = 0; i < n; ++i) {
            for (int tm = 0; tm < k; ++tm) {
                for (int dbit = 0; dbit < 2; ++dbit) {
                    int cur_dir = (dbit == 1 ? 1 : -1);

                    int ndir = cur_dir;
                    if (tm == d[i]) ndir = -ndir;

                    int tm1 = tm + 1;
                    if (tm1 == k) tm1 = 0;

                    int to = -1;
                    if (ndir == 1) {
                        if (i != n - 1) {
                            long long dist = p[i + 1] - p[i] - 1;
                            int tm2 = (tm1 + static_cast<int>(dist % k)) % k;
                            to = id(i + 1, tm2, dir_bit(1));
                        }
                    } else {
                        if (i != 0) {
                            long long dist = p[i] - p[i - 1] - 1;
                            int tm2 = (tm1 + static_cast<int>(dist % k)) % k;
                            to = id(i - 1, tm2, dir_bit(-1));
                        }
                    }

                    nxt[id(i, tm, dbit)] = to;
                }
            }
        }

        vector<char> state(S, 0);
        vector<int> in_stack_pos(S, -1);

        auto exits_from = [&](int start) {
            if (start == -1) return true;
            if (state[start] == 2) return true;
            if (state[start] == 3) return false;

            vector<int> st;
            int u = start;
            bool exit_result = false;

            while (true) {
                if (u == -1) {
                    exit_result = true;
                    break;
                }
                if (state[u] == 2) {
                    exit_result = true;
                    break;
                }
                if (state[u] == 3) {
                    exit_result = false;
                    break;
                }
                if (in_stack_pos[u] != -1) {
                    exit_result = false;
                    break;
                }

                in_stack_pos[u] = static_cast<int>(st.size());
                st.push_back(u);
                u = nxt[u];
            }

            for (int node : st) {
                state[node] = exit_result ? 2 : 3;
                in_stack_pos[node] = -1;
            }
            return exit_result;
        };

        for (int qi = 0; qi < q; ++qi) {
            long long start_pos = a[qi];

            int start_state = -1;
            auto it = lower_bound(p.begin(), p.end(), start_pos);

            if (it == p.end()) {
                start_state = -1;
            } else {
                int idx = static_cast<int>(it - p.begin());
                if (*it == start_pos) {
                    start_state = id(idx, 0, dir_bit(1));
                } else {
                    long long dist = p[idx] - start_pos;
                    int tm = static_cast<int>(dist % k);
                    start_state = id(idx, tm, dir_bit(1));
                }
            }

            cout << (exits_from(start_state) ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}

