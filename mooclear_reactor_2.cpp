#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> bit;
    Fenwick() : n(0) {}
    Fenwick(int n_) : n(n_), bit(n_ + 1, 0) {}

    void reset(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }

    void add(int idx, long long val) {
        for (; idx <= n; idx += idx & -idx) {
            bit[idx] += val;
        }
    }

    long long sumPrefix(int idx) const {
        long long res = 0;
        for (; idx > 0; idx -= idx & -idx) {
            res += bit[idx];
        }
        return res;
    }

    long long sumAll() const {
        return sumPrefix(n);
    }

    int findByOrder(long long k) const {
        int idx = 0;
        int bitMask = 1;
        while ((bitMask << 1) <= n) bitMask <<= 1;
        for (int step = bitMask; step > 0; step >>= 1) {
            int next = idx + step;
            if (next <= n && bit[next] < k) {
                k -= bit[next];
                idx = next;
            }
        }
        return idx + 1;
    }
};

static const long long NEG_INF = -(1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 0;
    if (!(cin >> t)) {
        return 0;
    }

    while (t--) {
        int n = 0, m = 0;
        cin >> n >> m;

        vector<vector<long long>> buckets(n + 2);
        vector<long long> energies;
        energies.reserve(n);

        for (int i = 0; i < n; ++i) {
            long long x = 0;
            int y = 0;
            cin >> x >> y;
            int d = y + 1; // size k requires d >= k
            buckets[d].push_back(x);
            energies.push_back(x);
        }

        vector<pair<long long, int>> shop(m);
        for (int i = 0; i < m; ++i) {
            long long x = 0;
            int y = 0;
            cin >> x >> y;
            shop[i] = {x, y};
        }

        vector<long long> cnt(n + 3, 0), sum_all(n + 3, 0);
        for (int k = n + 1; k >= 1; --k) {
            cnt[k] = cnt[k + 1] + (long long)buckets[k].size();
            long long addSum = 0;
            for (long long x : buckets[k]) addSum += x;
            sum_all[k] = sum_all[k + 1] + addSum;
        }

        vector<long long> values = energies;
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());

        Fenwick bitCount(values.size());
        Fenwick bitSum(values.size());

        vector<long long> g(n + 2, NEG_INF);
        vector<long long> kthVal(n + 2, 0);
        vector<long long> aVal(n + 2, NEG_INF);
        long long base_best = 0;

        auto addValue = [&](long long x) {
            int idx = (int)(lower_bound(values.begin(), values.end(), x) - values.begin()) + 1;
            bitCount.add(idx, 1);
            bitSum.add(idx, x);
        };

        auto prefixSumByCount = [&](long long t) {
            if (t <= 0) return 0LL;
            int idx = bitCount.findByOrder(t);
            long long cntBefore = bitCount.sumPrefix(idx - 1);
            long long sumBefore = bitSum.sumPrefix(idx - 1);
            long long remaining = t - cntBefore;
            long long valAt = values[idx - 1];
            return sumBefore + remaining * valAt;
        };

        auto sumLargest = [&](long long k) {
            long long totalCnt = bitCount.sumAll();
            if (totalCnt < k) return NEG_INF;
            long long totalSum = bitSum.sumAll();
            long long t = totalCnt - k;
            if (t == 0) return totalSum;
            long long sumSmallest = prefixSumByCount(t);
            return totalSum - sumSmallest;
        };

        auto kthLargestValue = [&](long long k) {
            long long totalCnt = bitCount.sumAll();
            long long order = totalCnt - k + 1; // kth largest -> order-th smallest
            int idx = bitCount.findByOrder(order);
            return values[idx - 1];
        };

        // Add particles with d = n + 1 (y = n), which are valid for all k <= n.
        for (long long x : buckets[n + 1]) {
            addValue(x);
        }

        for (int k = n; k >= 1; --k) {
            for (long long x : buckets[k]) {
                addValue(x);
            }
            if (cnt[k] >= k) {
                long long sumTop = sumLargest(k);
                long long kth = kthLargestValue(k);
                g[k] = sumTop;
                kthVal[k] = kth;
                aVal[k] = sumTop - kth;
                if (sumTop > base_best) base_best = sumTop;
            }
        }

        vector<long long> ext_best_prefix(n + 2, NEG_INF);
        for (int k = 1; k <= n + 1; ++k) {
            long long best = ext_best_prefix[k - 1];
            if (cnt[k] == k - 1) {
                best = max(best, sum_all[k]);
            }
            ext_best_prefix[k] = best;
        }

        struct Entry {
            long long b;
            int k;
            long long a;
        };

        vector<Entry> entries;
        entries.reserve(n);
        for (int k = 1; k <= n; ++k) {
            if (cnt[k] >= k) {
                entries.push_back({kthVal[k], k, aVal[k]});
            }
        }
        sort(entries.begin(), entries.end(), [](const Entry& e1, const Entry& e2) {
            if (e1.b != e2.b) return e1.b < e2.b;
            return e1.k < e2.k;
        });

        struct Query {
            long long x;
            int d;
            int idx;
        };

        vector<Query> queries;
        queries.reserve(m);
        for (int i = 0; i < m; ++i) {
            long long x = shop[i].first;
            int y = shop[i].second;
            int d = y + 1;
            queries.push_back({x, d, i});
        }

        sort(queries.begin(), queries.end(), [](const Query& q1, const Query& q2) {
            if (q1.x != q2.x) return q1.x < q2.x;
            return q1.idx < q2.idx;
        });

        struct FenwickMax {
            int n;
            vector<long long> bit;
            FenwickMax(int n_) : n(n_), bit(n_ + 1, NEG_INF) {}
            void update(int idx, long long val) {
                for (; idx <= n; idx += idx & -idx) {
                    bit[idx] = max(bit[idx], val);
                }
            }
            long long query(int idx) const {
                long long res = NEG_INF;
                for (; idx > 0; idx -= idx & -idx) {
                    res = max(res, bit[idx]);
                }
                return res;
            }
        };

        FenwickMax bitMax(n);
        vector<long long> answers(m, 0);

        size_t ptr = 0;
        for (const auto& q : queries) {
            while (ptr < entries.size() && entries[ptr].b < q.x) {
                bitMax.update(entries[ptr].k, entries[ptr].a);
                ++ptr;
            }
            int dCap = min(q.d, n);
            long long bestA = (dCap >= 1) ? bitMax.query(dCap) : NEG_INF;
            long long maxSwap = (bestA == NEG_INF) ? NEG_INF : bestA + q.x;

            int dExt = min(q.d, n + 1);
            long long bestExt = ext_best_prefix[dExt];
            long long maxExtend = (bestExt == NEG_INF) ? NEG_INF : bestExt + q.x;

            long long ans = base_best;
            if (maxSwap > ans) ans = maxSwap;
            if (maxExtend > ans) ans = maxExtend;

            answers[q.idx] = ans;
        }

        for (int i = 0; i < m; ++i) {
            if (i) cout << ' ';
            cout << answers[i];
        }
        cout << '\n';
    }
    return 0;
}
