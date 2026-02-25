#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 998244353;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> bal(n);
    bal[0] = (s[0] == '(' ? 1 : -1);
    for (int i = 1; i < n; i++) {
        bal[i] = bal[i - 1] + (s[i] == '(' ? 1 : -1);
    }

    vector<int> nxt_low(n + 1);
    nxt_low[n] = n;
    for (int i = n - 1; i >= 0; i--) {
        if (bal[i] < 2) {
            nxt_low[i] = i;
        } else {
            nxt_low[i] = nxt_low[i + 1];
        }
    }

    long long case1 = 0;
    {
        long long pw = 1;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                case1 = (case1 + pw) % MOD;
            }
            pw = pw * 2 % MOD;
        }
    }

    long long sum_f_close = 0;
    long long sum_g_close = 0;
    long long sum_f_active = 0;

    vector<long long> deact(n + 1, 0);

    long long mixed_ans = 0;
    long long all_close_ans = 0;

    for (int i = 0; i < n; i++) {
        sum_f_active = (sum_f_active - deact[i] % MOD + MOD) % MOD;

        if (s[i] == ')') {
            long long fi = (sum_f_close + sum_f_active) % MOD;
            long long gi = (1 + sum_g_close) % MOD;
            sum_f_close = (sum_f_close + fi) % MOD;
            sum_g_close = (sum_g_close + gi) % MOD;
            mixed_ans = (mixed_ans + fi) % MOD;
            all_close_ans = (all_close_ans + gi) % MOD;
        } else {
            if (bal[i] >= 2) {
                int lim = nxt_low[i];
                long long fi = (sum_f_close + sum_g_close + sum_f_active + 1) % MOD;
                int deact_at = lim + 1;
                sum_f_active = (sum_f_active + fi) % MOD;
                if (deact_at <= n) {
                    deact[deact_at] = (deact[deact_at] + fi) % MOD;
                }
            }
        }
    }

    long long ans = (case1 + mixed_ans + all_close_ans) % MOD;
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
