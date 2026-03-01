#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];

        priority_queue<pair<int,int>> pq;
        for (int i = 1; i <= n; ++i) {
            if (a[i] > 0) pq.push({a[i], i});
        }

        vector<pair<int,int>> talks;
        while (pq.size() >= 2) {
            auto [c1, i1] = pq.top(); pq.pop();
            auto [c2, i2] = pq.top(); pq.pop();
            talks.push_back({i1, i2});
            if (--c1 > 0) pq.push({c1, i1});
            if (--c2 > 0) pq.push({c2, i2});
        }

        cout << talks.size() << '\n';
        for (auto &p : talks) {
            cout << p.first << ' ' << p.second << '\n';
        }
    }

    return 0;
}
