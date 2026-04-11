#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    if (!(cin >> n)) return;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> ans(n, 0);

    for (int i = 0; i < n; i++) {
        int totalL = 0;
        vector<pair<long long, int>> events;
        events.reserve(n - i - 1);

        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[i]) {
                totalL++;
                long long sum = a[i] + a[j];
                long long x;
                if (sum % 2 != 0 && sum < 0) {
                    x = (sum - 1) / 2 + 1;
                } else {
                    x = sum >= 0 ? (sum - 1) / 2 + 1 : sum / 2;
                }

                auto floor_div = [](long long a, long long b) {
                    long long res = a / b;
                    long long rem = a % b;
                    if (rem != 0 && ((a < 0) ^ (b < 0))) {
                        res--;
                    }
                    return res;
                };

                x = floor_div(sum - 1, 2) + 1;

                events.push_back({x, -1});
            } else if (a[j] > a[i]) {
                long long sum = a[i] + a[j];

                auto floor_div = [](long long a, long long b) {
                    long long res = a / b;
                    long long rem = a % b;
                    if (rem != 0 && ((a < 0) ^ (b < 0))) {
                        res--;
                    }
                    return res;
                };

                long long x = floor_div(sum, 2) + 1;
                events.push_back({x, 1});
            }
        }

        sort(events.begin(), events.end());
        int cur = totalL;
        int max_val = cur;

        for (size_t k = 0; k < events.size(); ) {
            size_t j = k;
            while (j < events.size() && events[j].first == events[k].first) {
                cur += events[j].second;
                j++;
            }
            max_val = max(max_val, cur);
            k = j;
        }

        ans[i] = max_val;
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
