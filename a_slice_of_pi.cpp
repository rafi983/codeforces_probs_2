#include <algorithm>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

using ll = long long;

struct Point {
    int x;
    int y;
    ll v;
};

bool upper_half(int x, int y) {
    return y > 0 || (y == 0 && x > 0);
}

bool angle_less(const Point& a, const Point& b) {
    bool ha = upper_half(a.x, a.y);
    bool hb = upper_half(b.x, b.y);
    if (ha != hb) {
        return ha > hb;
    }
    ll cross = 1LL * a.x * b.y - 1LL * a.y * b.x;
    if (cross != 0) {
        return cross > 0;
    }
    if (a.x != b.x) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

bool same_direction(const Point& a, const Point& b) {
    return 1LL * a.x * b.y - 1LL * a.y * b.x == 0 && 1LL * a.x * b.x + 1LL * a.y * b.y > 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long double PI = acosl(-1.0L);
    const long double TWO_PI = 2.0L * PI;
    const long double EPS = 1e-18L;

    int t;
    cin >> t;

    while (t--) {
        int n;
        ll r, A;
        cin >> n >> r >> A;

        vector<Point> dirs;
        dirs.reserve(n);

        for (int i = 0; i < n; ++i) {
            int x, y;
            ll v;
            cin >> x >> y >> v;
            int g = gcd(abs(x), abs(y));
            dirs.push_back({x / g, y / g, v});
        }

        sort(dirs.begin(), dirs.end(), angle_less);

        vector<long double> angle;
        vector<ll> weight;
        angle.reserve(n);
        weight.reserve(n);

        for (int i = 0; i < n; ++i) {
            if (i > 0 && same_direction(dirs[i - 1], dirs[i])) {
                weight.back() += dirs[i].v;
            } else {
                long double a = atan2l((long double)dirs[i].y, (long double)dirs[i].x);
                if (a < 0) {
                    a += TWO_PI;
                }
                angle.push_back(a);
                weight.push_back(dirs[i].v);
            }
        }

        int m = (int)weight.size();
        vector<long double> ext_angle(2 * m + 1, 0);
        vector<ll> prefix(2 * m + 1, 0);

        for (int i = 1; i <= m; ++i) {
            ext_angle[i] = angle[i - 1];
            prefix[i] = prefix[i - 1] + weight[i - 1];
        }
        for (int i = 1; i <= m; ++i) {
            ext_angle[i + m] = angle[i - 1] + TWO_PI;
            prefix[i + m] = prefix[i + m - 1] + weight[i - 1];
        }

        long double max_angle = 2.0L * (long double)A / ((long double)r * (long double)r);
        if (max_angle > TWO_PI) {
            max_angle = TWO_PI;
        }

        deque<int> min_pref;
        deque<int> max_pref;
        int left_by_angle = 1;
        ll answer = 0;

        for (int i = 1; i <= 2 * m; ++i) {
            int k = i - 1;
            while (!min_pref.empty() && prefix[min_pref.back()] >= prefix[k]) {
                min_pref.pop_back();
            }
            min_pref.push_back(k);
            while (!max_pref.empty() && prefix[max_pref.back()] <= prefix[k]) {
                max_pref.pop_back();
            }
            max_pref.push_back(k);

            while (left_by_angle <= i && ext_angle[i] - ext_angle[left_by_angle] > max_angle + EPS) {
                ++left_by_angle;
            }
            int left_prefix = max(i - m, left_by_angle - 1);

            while (!min_pref.empty() && min_pref.front() < left_prefix) {
                min_pref.pop_front();
            }
            while (!max_pref.empty() && max_pref.front() < left_prefix) {
                max_pref.pop_front();
            }

            if (!min_pref.empty()) {
                answer = max(answer, prefix[i] - prefix[min_pref.front()]);
            }
            if (!max_pref.empty()) {
                answer = max(answer, prefix[max_pref.front()] - prefix[i]);
            }
        }

        cout << answer << '\n';
    }

    return 0;
}
