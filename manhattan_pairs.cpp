#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<Point> p(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i].x >> p[i].y;
            p[i].id = i + 1;
        }

        sort(p.begin(), p.end(), [](const Point& a, const Point& b) {
            if (a.x != b.x) return a.x < b.x;
            if (a.y != b.y) return a.y < b.y;
            return a.id < b.id;
        });

        int k = n / 2;
        vector<Point> left(p.begin(), p.begin() + k), right(p.begin() + k, p.end());

        sort(left.begin(), left.end(), [](const Point& a, const Point& b) {
            if (a.y != b.y) return a.y < b.y;
            return a.id < b.id;
        });
        sort(right.begin(), right.end(), [](const Point& a, const Point& b) {
            if (a.y != b.y) return a.y > b.y;
            return a.id < b.id;
        });

        for (int i = 0; i < k; ++i) {
            cout << left[i].id << ' ' << right[i].id << '\n';
        }
    }

    return 0;
}
