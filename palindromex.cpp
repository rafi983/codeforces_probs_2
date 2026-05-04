#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int m = 2 * n;

        vector<int> a(m + 1);
        for (int i = 1; i <= m; ++i) cin >> a[i];

        vector<int> first(n, -1), second(n, -1);
        for (int i = 1; i <= m; ++i) {
            int v = a[i];
            if (first[v] == -1) first[v] = i;
            else second[v] = i;
        }

        vector<int> pair_sum(n);
        for (int v = 0; v < n; ++v) pair_sum[v] = first[v] + second[v];

        vector<int> label(m + 1);
        for (int i = 1; i <= m; ++i) label[i] = pair_sum[a[i]];

        vector<int> seen(n + 1, 0);
        int token = 1;

        int answer = 0;

        auto run_center = [&](int center_sum, int left_start, int right_start, bool has_center_value, int center_value) {
            ++token;
            int mex = 0;

            auto add_value = [&](int v) {
                if (seen[v] != token) {
                    seen[v] = token;
                    while (mex <= n && seen[mex] == token) ++mex;
                }
            };

            if (has_center_value) {
                add_value(center_value);
                answer = max(answer, mex);
            }

            int l = left_start, r = right_start;
            while (l >= 1 && r <= m && label[l] == center_sum) {
                add_value(a[l]);
                answer = max(answer, mex);
                --l;
                ++r;
            }
        };

        for (int c = 1; c <= m; ++c) {
            int s = 2 * c;
            run_center(s, c - 1, c + 1, true, a[c]);
        }

        for (int c = 1; c < m; ++c) {
            int s = 2 * c + 1;
            run_center(s, c, c + 1, false, -1);
        }

        cout << answer << '\n';
    }

    return 0;
}
