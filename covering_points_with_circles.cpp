#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct Point {
    int x;
    int y;
};

static inline long long floor_div(long long a, long long b) {
    long long q = a / b;
    long long r = a % b;
    if (r != 0 && ((r > 0) != (b > 0))) --q;
    return q;
}

struct RNG {
    uint64_t s;
    explicit RNG(uint64_t seed) : s(seed) {}
    uint64_t next() {
        s ^= s << 7;
        s ^= s >> 9;
        return s * 11995408973635179863ULL;
    }
    int nextInt(int mod) {
        return (int)(next() % (uint64_t)mod);
    }
};

class Solver {
public:
    int n;
    int r;
    long long rr;
    long long dx;
    long long dy;
    vector<Point> p;

    Solver(int n_, int r_, vector<Point> pts) : n(n_), r(r_), rr(1LL * r_ * r_), dx(2LL * r_), dy((long long)ceill(sqrtl(3.0L) * (long double)r_)), p(std::move(pts)) {}

    static inline long long ceil_div(long long a, long long b) {
        return -floor_div(-a, b);
    }

    bool coveredByOffset(const Point& pt, int ox, int oy, long long& cxOut, long long& cyOut) const {
        long long py = pt.y;
        long long px = pt.x;
        long long j0 = floor_div(py - oy, dy);
        for (long long j = j0 - 2; j <= j0 + 2; ++j) {
            long long cy = (long long)oy + j * dy;
            long long vy = py - cy;
            if (vy > r || vy < -r) continue;

            long long rem = rr - vy * vy;
            long long lim = (long long)floor(sqrt((long double)rem));
            long long rowShift = ((j & 1LL) ? r : 0);
            long long x0 = (long long)ox + rowShift;

            long long iL = ceil_div(px - lim - x0, dx);
            long long iR = floor_div(px + lim - x0, dx);
            for (long long i = iL; i <= iR; ++i) {
                long long cx = x0 + i * dx;
                long long vx = px - cx;
                if (vx * vx + vy * vy <= rr) {
                    cxOut = cx;
                    cyOut = cy;
                    return true;
                }
            }
        }
        return false;
    }

    int scoreOffset(int ox, int oy, int stopAt = -1, int mustBeat = -1) const {
        int covered = 0;
        long long cx, cy;
        for (int idx = 0; idx < n; ++idx) {
            const auto& pt = p[idx];
            if (coveredByOffset(pt, ox, oy, cx, cy)) ++covered;
            if (stopAt >= 0 && covered >= stopAt) return covered;
            if (mustBeat >= 0) {
                int remaining = n - idx - 1;
                if (covered + remaining <= mustBeat) return covered;
            }
        }
        return covered;
    }

    vector<pair<int, int>> buildCenters(int ox, int oy, int& coveredCount) const {
        unordered_set<uint64_t> used;
        used.reserve((size_t)n * 2);
        vector<pair<int, int>> centers;
        centers.reserve(n);
        coveredCount = 0;

        long long cx, cy;
        for (const auto& pt : p) {
            if (!coveredByOffset(pt, ox, oy, cx, cy)) continue;
            ++coveredCount;
            if (cx < -200000 || cx > 200000 || cy < -200000 || cy > 200000) continue;
            uint64_t key = (uint64_t)(uint32_t)(cx + 200000) << 21 ^ (uint64_t)(uint32_t)(cy + 200000);
            if (used.insert(key).second) {
                centers.push_back({(int)cx, (int)cy});
            }
        }

        if (centers.empty()) {
            centers.push_back({p[0].x, p[0].y});
        }

        return centers;
    }

    pair<int, int> findBestOffset() const {
        int need = (89 * n + 99) / 100;
        int bestOx = 0;
        int bestOy = 0;
        int bestScore = -1;

        int gx = min<int>((int)dx, 24);
        int gy = min<int>((int)dy, 24);

        for (int ix = 0; ix < gx; ++ix) {
            int ox = (int)((ix * dx) / gx);
            for (int iy = 0; iy < gy; ++iy) {
                int oy = (int)((iy * dy) / gy);
                int sc = scoreOffset(ox, oy, need, bestScore);
                if (sc > bestScore) {
                    bestScore = sc;
                    bestOx = ox;
                    bestOy = oy;
                    if (bestScore >= need) return {bestOx, bestOy};
                }
            }
        }

        RNG rng(146527ULL + (uint64_t)n * 19260817ULL + (uint64_t)r * 998244353ULL);
        int randomTrials = min(1800, 250 + (int)(12.0 * sqrt((double)n) + 70.0 * log2((double)r + 2.0)));
        for (int it = 0; it < randomTrials; ++it) {
            int ox = rng.nextInt((int)dx);
            int oy = rng.nextInt((int)dy);
            int sc = scoreOffset(ox, oy, need, bestScore);
            if (sc > bestScore) {
                bestScore = sc;
                bestOx = ox;
                bestOy = oy;
                if (bestScore >= need) return {bestOx, bestOy};
            }
        }

        int stepX = max(1, (int)dx / 6);
        int stepY = max(1, (int)dy / 6);
        int rounds = 0;
        while ((stepX > 0 || stepY > 0) && rounds < 12) {
            ++rounds;
            bool improved = false;
            const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            for (int d = 0; d < 4; ++d) {
                int sx = dirs[d][0] * stepX;
                int sy = dirs[d][1] * stepY;
                int nox = bestOx + sx;
                int noy = bestOy + sy;
                nox %= (int)dx;
                noy %= (int)dy;
                if (nox < 0) nox += (int)dx;
                if (noy < 0) noy += (int)dy;
                int sc = scoreOffset(nox, noy, need, bestScore);
                if (sc > bestScore) {
                    bestScore = sc;
                    bestOx = nox;
                    bestOy = noy;
                    improved = true;
                    if (bestScore >= need) return {bestOx, bestOy};
                }
            }
            if (!improved) {
                const int diag[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
                for (int d = 0; d < 4; ++d) {
                    int sx = diag[d][0] * stepX;
                    int sy = diag[d][1] * stepY;
                    int nox = bestOx + sx;
                    int noy = bestOy + sy;
                    nox %= (int)dx;
                    noy %= (int)dy;
                    if (nox < 0) nox += (int)dx;
                    if (noy < 0) noy += (int)dy;
                    int sc = scoreOffset(nox, noy, need, bestScore);
                    if (sc > bestScore) {
                        bestScore = sc;
                        bestOx = nox;
                        bestOy = noy;
                        improved = true;
                        if (bestScore >= need) return {bestOx, bestOy};
                    }
                }
            }
            if (!improved) {
                if (stepX > 1) stepX /= 2;
                else stepX = 0;
                if (stepY > 1) stepY /= 2;
                else stepY = 0;
            }
            if (bestScore >= need) break;
        }

        return {bestOx, bestOy};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, r;
    cin >> n >> r;

    vector<Point> pts(n);
    for (int i = 0; i < n; ++i) cin >> pts[i].x >> pts[i].y;

    Solver solver(n, r, pts);
    auto [ox, oy] = solver.findBestOffset();

    int coveredCount = 0;
    vector<pair<int, int>> centers = solver.buildCenters(ox, oy, coveredCount);

    if ((int)centers.size() > n) centers.resize(n);

    cout << centers.size() << '\n';
    for (auto& c : centers) {
        cout << c.first << ' ' << c.second << '\n';
    }

    return 0;
}

