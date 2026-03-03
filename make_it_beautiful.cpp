#include <bits/stdc++.h>
using namespace std;

static inline long long next_upgrade_cost(unsigned long long x) {
    return static_cast<long long>((~x) & (x + 1ULL));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        long long k;
        cin >> n >> k;

        vector<unsigned long long> a(n);
        long long beauty = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            beauty += __builtin_popcountll(a[i]);
        }

        using Node = pair<long long, int>;
        priority_queue<Node, vector<Node>, greater<Node>> pq;

        for (int i = 0; i < n; ++i) {
            pq.push({next_upgrade_cost(a[i]), i});
        }

        while (!pq.empty()) {
            auto [cost, idx] = pq.top();
            if (cost > k) break;
            pq.pop();

            k -= cost;
            beauty += 1;
            a[idx] += static_cast<unsigned long long>(cost);

            pq.push({next_upgrade_cost(a[idx]), idx});
        }

        cout << beauty << '\n';
    }

    return 0;
}

