#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x;
    int y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<Point> pts(n);
        vector<int> ys(n);
        for (int i = 0; i < n; ++i) {
            cin >> pts[i].x >> pts[i].y;
            ys[i] = pts[i].y;
        }

        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        for (int i = 0; i < n; ++i) {
            pts[i].y = (int)(lower_bound(ys.begin(), ys.end(), pts[i].y) - ys.begin());
        }

        sort(pts.begin(), pts.end(), [](const Point &a, const Point &b) {
            if (a.x != b.x) return a.x < b.x;
            return a.y < b.y;
        });

        int m = (int)ys.size();
        vector<int> left_cnt(m, 0), right_cnt(m, 0);
        for (const auto &p : pts) ++right_cnt[p.y];

        int left_min = m, left_max = -1;
        int right_min = 0, right_max = m - 1;
        while (right_min < m && right_cnt[right_min] == 0) ++right_min;
        while (right_max >= 0 && right_cnt[right_max] == 0) --right_max;

        long long ans = 0;
        int pos = 0;
        while (pos < n) {
            int cur_x = pts[pos].x;
            while (pos < n && pts[pos].x == cur_x) {
                int y = pts[pos].y;

                ++left_cnt[y];
                --right_cnt[y];

                if (y < left_min) left_min = y;
                if (y > left_max) left_max = y;

                ++pos;
            }

            if (pos == n) break;

            while (right_min < m && right_cnt[right_min] == 0) ++right_min;
            while (right_max >= 0 && right_cnt[right_max] == 0) --right_max;

            int low = max(left_min, right_min);
            int high = min(left_max, right_max);
            if (high > low) ans += (high - low);
        }

        cout << ans << '\n';
    }

    return 0;
}
