#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class SegTreeMax {
public:
    explicit SegTreeMax(int n = 0) { init(n); }

    void init(int n_) {
        n = 1;
        while (n < n_) n <<= 1;
        t.assign(2 * n, 0);
    }

    void set_val(int pos, int val) {
        int p = pos + n;
        t[p] = val;
        p >>= 1;
        while (p > 0) {
            t[p] = max(t[p << 1], t[p << 1 | 1]);
            p >>= 1;
        }
    }

    int all_max() const {
        return t[1];
    }

private:
    int n;
    vector<int> t;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<int> a(n + 1), b(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) cin >> b[i];

        int vmax = n;

        vector<vector<int>> mx(2, vector<int>(vmax + 1, 0));
        for (int i = 1; i <= n; ++i) {
            int pa = i & 1;
            int pb = pa ^ 1;
            mx[pa][a[i]] = max(mx[pa][a[i]], i);
            mx[pb][b[i]] = max(mx[pb][b[i]], i);
        }

        int best_no_delete = 0;
        for (int x = 1; x <= vmax; ++x) {
            best_no_delete = max(best_no_delete, min(mx[0][x], mx[1][x]));
        }

        vector<vector<int>> pref(2, vector<int>(vmax + 1, 0));

        vector<vector<int>> events(n + 2);
        for (int x = 1; x <= vmax; ++x) {
            if (mx[0][x] > 0) events[mx[0][x]].push_back(x);
            if (mx[1][x] > 0) events[mx[1][x]].push_back(x);
        }

        auto calc_cand = [&](int x, int k) -> int {
            int right_from_1 = (mx[1][x] > k ? mx[1][x] - 1 : 0);
            int right_from_0 = (mx[0][x] > k ? mx[0][x] - 1 : 0);

            int last0 = max(pref[0][x], right_from_1);
            int last1 = max(pref[1][x], right_from_0);
            return min(last0, last1);
        };

        SegTreeMax seg(vmax + 1);
        vector<int> cand(vmax + 1, 0);
        for (int x = 1; x <= vmax; ++x) {
            cand[x] = calc_cand(x, 1);
            seg.set_val(x, cand[x]);
        }

        int best_with_delete = 0;
        vector<int> touched;
        touched.reserve(8);
        vector<int> seen(vmax + 1, 0);
        int stamp = 1;

        for (int k = 1; k <= n; ++k) {
            best_with_delete = max(best_with_delete, seg.all_max());
            if (k == n) break;

            int ca = k & 1;
            int cb = ca ^ 1;
            pref[ca][a[k]] = k;
            pref[cb][b[k]] = k;

            int nk = k + 1;
            touched.clear();

            auto add_touch = [&](int x) {
                if (seen[x] == stamp) return;
                seen[x] = stamp;
                touched.push_back(x);
            };

            add_touch(a[k]);
            add_touch(b[k]);
            for (int x : events[nk]) add_touch(x);

            for (int x : touched) {
                cand[x] = calc_cand(x, nk);
                seg.set_val(x, cand[x]);
            }

            ++stamp;
            if (stamp == 0) {
                fill(seen.begin(), seen.end(), 0);
                stamp = 1;
            }
        }

        cout << max(best_no_delete, best_with_delete) << '\n';
    }

    return 0;
}

