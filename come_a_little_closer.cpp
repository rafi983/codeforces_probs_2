#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Point {
    long long x;
    long long y;
};

static long long eval_after_remove(
    int idx,
    const vector<Point>& p,
    long long minX1,
    int cntMinX1,
    long long minX2,
    long long maxX1,
    int cntMaxX1,
    long long maxX2,
    long long minY1,
    int cntMinY1,
    long long minY2,
    long long maxY1,
    int cntMaxY1,
    long long maxY2,
    int n
) {
    long long mnX = (p[idx].x == minX1 && cntMinX1 == 1) ? minX2 : minX1;
    long long mxX = (p[idx].x == maxX1 && cntMaxX1 == 1) ? maxX2 : maxX1;
    long long mnY = (p[idx].y == minY1 && cntMinY1 == 1) ? minY2 : minY1;
    long long mxY = (p[idx].y == maxY1 && cntMaxY1 == 1) ? maxY2 : maxY1;

    long long w = mxX - mnX + 1;
    long long h = mxY - mnY + 1;
    long long area = w * h;

    if (area > n - 1) {
        return area;
    }

    long long option1 = (w + 1) * h;
    long long option2 = w * (h + 1);
    return min(option1, option2);
}

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
        }

        if (n == 1) {
            cout << 1 << '\n';
            continue;
        }

        const long long INF = numeric_limits<long long>::max() / 4;

        long long minX1 = INF, minX2 = INF, maxX1 = -INF, maxX2 = -INF;
        long long minY1 = INF, minY2 = INF, maxY1 = -INF, maxY2 = -INF;
        int cntMinX1 = 0, cntMaxX1 = 0, cntMinY1 = 0, cntMaxY1 = 0;

        for (int i = 0; i < n; ++i) {
            long long x = p[i].x;
            long long y = p[i].y;

            if (x < minX1) {
                minX2 = minX1;
                minX1 = x;
                cntMinX1 = 1;
            } else if (x == minX1) {
                ++cntMinX1;
            } else if (x < minX2) {
                minX2 = x;
            }

            if (x > maxX1) {
                maxX2 = maxX1;
                maxX1 = x;
                cntMaxX1 = 1;
            } else if (x == maxX1) {
                ++cntMaxX1;
            } else if (x > maxX2) {
                maxX2 = x;
            }

            if (y < minY1) {
                minY2 = minY1;
                minY1 = y;
                cntMinY1 = 1;
            } else if (y == minY1) {
                ++cntMinY1;
            } else if (y < minY2) {
                minY2 = y;
            }

            if (y > maxY1) {
                maxY2 = maxY1;
                maxY1 = y;
                cntMaxY1 = 1;
            } else if (y == maxY1) {
                ++cntMaxY1;
            } else if (y > maxY2) {
                maxY2 = y;
            }
        }

        long long baseW = maxX1 - minX1 + 1;
        long long baseH = maxY1 - minY1 + 1;
        long long ans = baseW * baseH;

        vector<int> cand;
        cand.reserve(8);
        for (int i = 0; i < n; ++i) {
            if (p[i].x == minX1 || p[i].x == maxX1 || p[i].y == minY1 || p[i].y == maxY1) {
                cand.push_back(i);
            }
        }
        sort(cand.begin(), cand.end());
        cand.erase(unique(cand.begin(), cand.end()), cand.end());

        for (int idx : cand) {
            long long cur = eval_after_remove(
                idx,
                p,
                minX1, cntMinX1, minX2,
                maxX1, cntMaxX1, maxX2,
                minY1, cntMinY1, minY2,
                maxY1, cntMaxY1, maxY2,
                n
            );
            ans = min(ans, cur);
        }

        cout << ans << '\n';
    }

    return 0;
}

