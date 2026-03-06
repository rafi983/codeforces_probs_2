#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        long long L;
        cin >> n >> m >> L;

        vector<pair<long long, long long>> hurdles(n);
        for (int i = 0; i < n; ++i) {
            cin >> hurdles[i].first >> hurdles[i].second;
        }

        vector<pair<long long, long long>> powerups(m);
        for (int i = 0; i < m; ++i) {
            cin >> powerups[i].first >> powerups[i].second;
        }

        priority_queue<long long> available;
        long long jump = 1;
        int used = 0;
        int ptr = 0;
        bool ok = true;

        for (int i = 0; i < n; ++i) {
            long long l = hurdles[i].first;
            long long r = hurdles[i].second;

            while (ptr < m && powerups[ptr].first < l) {
                available.push(powerups[ptr].second);
                ++ptr;
            }

            long long need = r - l + 2;
            while (jump < need && !available.empty()) {
                jump += available.top();
                available.pop();
                ++used;
            }

            if (jump < need) {
                ok = false;
                break;
            }
        }

        cout << (ok ? used : -1) << '\n';
    }

    return 0;
}

