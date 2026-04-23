#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

static inline int id(char ch) {
    if (ch == 'R') return 0;
    if (ch == 'G') return 1;
    return 2;
}

static inline char ch(int i) {
    return i == 0 ? 'R' : (i == 1 ? 'G' : 'B');
}

static inline bool okPlace(const string& s, char c) {
    int m = (int)s.size();
    if (m >= 1 && s[m - 1] == c) return false;
    if (m >= 3 && s[m - 3] == c) return false;
    return true;
}

static inline long long maxAdjLen(long long a, long long b, long long c) {
    long long sum = a + b + c;
    long long mx = max(a, max(b, c));
    long long oth = sum - mx;
    return min(sum, 2 * oth + 1);
}

string buildOne(long long r, long long g, long long b) {
    long long cnt[3] = {r, g, b};
    long long target = maxAdjLen(r, g, b);

    auto canFinishAdj = [&](long long a, long long bb, long long cc, long long need) -> bool {
        if (need < 0) return false;
        long long sum = a + bb + cc;
        if (need > sum) return false;
        if (need == 0) return true;
        long long mx = max(a, max(bb, cc));
        long long oth = sum - mx;
        return need <= min(sum, 2 * oth + 1);
    };

    auto attempt = [&](long long want, const int ord[3], int mode, int forcedFirst) -> string {
        long long c[3] = {cnt[0], cnt[1], cnt[2]};
        string s;
        s.reserve((size_t)want);

        for (long long pos = 0; pos < want; ++pos) {
            int best = -1;
            long long bestA = -1;
            long long bestB = -1;
            long long bestC = -1;
            long long bestD = -1;

            int rankPos[3];
            rankPos[ord[0]] = 0;
            rankPos[ord[1]] = 1;
            rankPos[ord[2]] = 2;

            for (int color = 0; color < 3; ++color) {
                if (c[color] == 0) continue;
                if (pos == 0 && forcedFirst != -1 && color != forcedFirst) continue;
                char cc = ch(color);
                if (!okPlace(s, cc)) continue;

                --c[color];
                long long remNeed = want - pos - 1;
                bool goodAdj = canFinishAdj(c[0], c[1], c[2], remNeed);

                bool hasNext = true;
                if (remNeed > 0) {
                    hasNext = false;
                    for (int nx = 0; nx < 3; ++nx) {
                        if (c[nx] == 0) continue;
                        if (nx == color) continue;
                        if ((int)s.size() >= 2 && id(s[s.size() - 2]) == nx) continue;
                        hasNext = true;
                        break;
                    }
                }

                long long A = (goodAdj ? 1LL : 0LL);
                long long B = (hasNext ? 1LL : 0LL);
                long long C = (mode == 0 ? c[color] : -c[color]);
                long long D = -rankPos[color];

                if (A > bestA || (A == bestA && (B > bestB || (B == bestB && (C > bestC || (C == bestC && D > bestD)))))) {
                    bestA = A;
                    bestB = B;
                    bestC = C;
                    bestD = D;
                    best = color;
                }
                ++c[color];
            }

            if (best == -1) break;
            s.push_back(ch(best));
            --c[best];
        }
        return s;
    };

    const int perms[6][3] = {
        {0, 1, 2}, {0, 2, 1}, {1, 0, 2},
        {1, 2, 0}, {2, 0, 1}, {2, 1, 0}
    };

    string bestGlobal;
    for (long long want = target; want >= max(0LL, target - 24); --want) {
        string bestForWant;
        for (int p = 0; p < 6; ++p) {
            for (int mode = 0; mode < 2; ++mode) {
                string s = attempt(want, perms[p], mode, -1);
                if ((long long)s.size() > (long long)bestForWant.size()) bestForWant = s;
                for (int first = 0; first < 3; ++first) {
                    s = attempt(want, perms[p], mode, first);
                    if ((long long)s.size() > (long long)bestForWant.size()) bestForWant = s;
                }
            }
        }
        if ((long long)bestForWant.size() == want) return bestForWant;
        if (bestForWant.size() > bestGlobal.size()) bestGlobal = bestForWant;
    }

    return bestGlobal;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long r, g, b;
        cin >> r >> g >> b;
        cout << buildOne(r, g, b) << '\n';
    }
    return 0;
}

