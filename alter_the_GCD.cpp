#include <bits/stdc++.h>
using namespace std;

struct GcdSegment {
    int l;
    int r;
    long long g;
};

struct PairSegment {
    int l;
    int r;
    long long x;
    long long y;
};

vector<pair<long long, int>> extend_gcd_segments(const vector<pair<long long, int>>& prev, long long value, int pos) {
    vector<pair<long long, int>> cur;
    cur.push_back({value, pos});

    for (auto [g, start] : prev) {
        long long ng = gcd(g, value);
        if (cur.back().first == ng) {
            cur.back().second = start;
        } else {
            cur.push_back({ng, start});
        }
    }

    return cur;
}

vector<GcdSegment> materialize_segments(const vector<pair<long long, int>>& states, int r) {
    vector<GcdSegment> segments;
    segments.reserve(states.size());

    for (int i = (int)states.size() - 1; i >= 0; --i) {
        int l = states[i].second;
        int rr = (i == 0 ? r : states[i - 1].second - 1);
        segments.push_back({l, rr, states[i].first});
    }

    return segments;
}

void solve() {
    int n;
    cin >> n;

    vector<long long> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }

    vector<long long> prefA(n + 1, 0), prefB(n + 1, 0), sufA(n + 2, 0), sufB(n + 2, 0);
    for (int i = 1; i <= n; ++i) {
        prefA[i] = gcd(prefA[i - 1], a[i]);
        prefB[i] = gcd(prefB[i - 1], b[i]);
    }
    for (int i = n; i >= 1; --i) {
        sufA[i] = gcd(sufA[i + 1], a[i]);
        sufB[i] = gcd(sufB[i + 1], b[i]);
    }

    vector<PairSegment> prefixSegments;
    int start = 1;
    long long curX = prefA[0];
    long long curY = prefB[0];
    for (int l = 2; l <= n; ++l) {
        long long nextX = prefA[l - 1];
        long long nextY = prefB[l - 1];
        if (nextX != curX || nextY != curY) {
            prefixSegments.push_back({start, l - 1, curX, curY});
            start = l;
            curX = nextX;
            curY = nextY;
        }
    }
    prefixSegments.push_back({start, n, curX, curY});

    long long bestValue = -1;
    long long ways = 0;

    vector<pair<long long, int>> statesA;
    vector<pair<long long, int>> statesB;

    for (int r = 1; r <= n; ++r) {
        statesA = extend_gcd_segments(statesA, a[r], r);
        statesB = extend_gcd_segments(statesB, b[r], r);

        vector<GcdSegment> segA = materialize_segments(statesA, r);
        vector<GcdSegment> segB = materialize_segments(statesB, r);

        vector<PairSegment> insideSegments;
        insideSegments.reserve(segA.size() + segB.size());

        int i = 0, j = 0;
        while (i < (int)segA.size() && j < (int)segB.size()) {
            int l = max(segA[i].l, segB[j].l);
            int rr = min(segA[i].r, segB[j].r);
            if (l <= rr) {
                insideSegments.push_back({l, rr, segA[i].g, segB[j].g});
            }
            if (segA[i].r < segB[j].r) {
                ++i;
            } else {
                ++j;
            }
        }

        long long suffixA = sufA[r + 1];
        long long suffixB = sufB[r + 1];

        i = 0;
        j = 0;
        while (i < (int)insideSegments.size() && j < (int)prefixSegments.size()) {
            int l = max(insideSegments[i].l, prefixSegments[j].l);
            int rr = min(insideSegments[i].r, prefixSegments[j].r);
            if (l <= rr) {
                long long gcdFirst = gcd(gcd(prefixSegments[j].x, insideSegments[i].y), suffixA);
                long long gcdSecond = gcd(gcd(prefixSegments[j].y, insideSegments[i].x), suffixB);
                long long value = gcdFirst + gcdSecond;
                long long count = rr - l + 1LL;

                if (value > bestValue) {
                    bestValue = value;
                    ways = count;
                } else if (value == bestValue) {
                    ways += count;
                }
            }

            if (insideSegments[i].r < prefixSegments[j].r) {
                ++i;
            } else {
                ++j;
            }
        }
    }

    cout << bestValue << ' ' << ways << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

