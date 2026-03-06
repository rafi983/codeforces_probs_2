#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        long long m;
        cin >> n >> m >> k;

        vector<long long> h(n), x(n);
        for (int i = 0; i < n; ++i) {
            cin >> h[i];
        }
        for (int i = 0; i < n; ++i) {
            cin >> x[i];
        }

        long long max_health = 0;
        for (long long value : h) {
            max_health = max(max_health, value);
        }

        auto can = [&](long long attacks) {
            vector<pair<long long, int>> events;
            events.reserve(2 * n);

            for (int i = 0; i < n; ++i) {
                long long need = (h[i] + attacks - 1) / attacks;
                if (need > m) {
                    continue;
                }

                long long reach = m - need;
                long long left = x[i] - reach;
                long long right = x[i] + reach;
                events.push_back({left, 1});
                events.push_back({right + 1, -1});
            }

            sort(events.begin(), events.end());

            int covered = 0;
            int idx = 0;
            while (idx < (int)events.size()) {
                long long position = events[idx].first;
                while (idx < (int)events.size() && events[idx].first == position) {
                    covered += events[idx].second;
                    ++idx;
                }
                if (covered >= k) {
                    return true;
                }
            }

            return false;
        };

        if (!can(max_health)) {
            cout << -1 << '\n';
            continue;
        }

        long long left = 1, right = max_health;
        while (left < right) {
            long long mid = left + (right - left) / 2;
            if (can(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        cout << left << '\n';
    }

    return 0;
}

