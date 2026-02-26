#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) {
        return 0;
    }
    while (T--) {
        int n;
        cin >> n;
        string X;
        cin >> X;

        int cnt_a = (n + 1) / 2; // in T
        int cnt_b = n / 2;

        int fixed_a = 0, fixed_b = 0, q = 0;
        for (char c : X) {
            if (c == 'a') fixed_a++;
            else if (c == 'b') fixed_b++;
            else if (c == '?') q++;
        }

        bool ok = true;
        if (fixed_a > cnt_a || fixed_b > cnt_b) ok = false;
        int needed_a = cnt_a - fixed_a;
        if (needed_a < 0 || needed_a > q) ok = false;

        if (!ok) {
            cout << "NO\n";
            continue;
        }

        const int INF = (int)1e9;
        bool dp_cur[2] = {false, false}, dp_nxt[2] = {false, false};
        int lo_cur[2] = {INF, INF}, hi_cur[2] = {-INF, -INF};
        int lo_nxt[2], hi_nxt[2];

        dp_cur[0] = true;
        lo_cur[0] = hi_cur[0] = 0; // 0 'a's used at start

        for (int i = 0; i < n; ++i) {
            dp_nxt[0] = dp_nxt[1] = false;
            lo_nxt[0] = lo_nxt[1] = INF;
            hi_nxt[0] = hi_nxt[1] = -INF;

            for (int pl = 0; pl < 2; ++pl) {
                if (!dp_cur[pl]) continue;
                int len = n - i;
                int pr = (pl + len - 1) & 1; // right parity
                char chL = (pl == 0 ? 'a' : 'b');
                char chR = (pr == 0 ? 'a' : 'b');

                auto relax = [&](int pl_next, char ch) {
                    if (!(X[i] == ch || X[i] == '?')) return;
                    int delta = (ch == 'a');
                    int cand_lo = lo_cur[pl] + delta;
                    int cand_hi = hi_cur[pl] + delta;
                    if (!dp_nxt[pl_next]) {
                        dp_nxt[pl_next] = true;
                        lo_nxt[pl_next] = cand_lo;
                        hi_nxt[pl_next] = cand_hi;
                    } else {
                        lo_nxt[pl_next] = min(lo_nxt[pl_next], cand_lo);
                        hi_nxt[pl_next] = max(hi_nxt[pl_next], cand_hi);
                    }
                };

                // take from left
                relax(pl ^ 1, chL);
                // take from right
                relax(pl, chR);
            }

            dp_cur[0] = dp_nxt[0];
            dp_cur[1] = dp_nxt[1];
            lo_cur[0] = lo_nxt[0];
            lo_cur[1] = lo_nxt[1];
            hi_cur[0] = hi_nxt[0];
            hi_cur[1] = hi_nxt[1];
        }

        if (!dp_cur[0] && !dp_cur[1]) {
            cout << "NO\n";
            continue;
        }

        int minA = INF, maxA = -INF;
        for (int pl = 0; pl < 2; ++pl) {
            if (!dp_cur[pl]) continue;
            minA = min(minA, lo_cur[pl]);
            maxA = max(maxA, hi_cur[pl]);
        }

        if (minA <= cnt_a && cnt_a <= maxA) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}

