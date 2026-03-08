#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int color_bit(char c) {
    if (c == 'B') return 1;
    if (c == 'G') return 2;
    if (c == 'R') return 4;
    return 8;
}

int mask_from_string(const string &s) {
    return color_bit(s[0]) | color_bit(s[1]);
}

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> city_mask(n + 1);
    vector<vector<int>> positions(16);

    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        city_mask[i] = mask_from_string(s);
        positions[city_mask[i]].push_back(i);
    }

    while (q--) {
        int x, y;
        cin >> x >> y;

        if (x > y) {
            swap(x, y);
        }

        int left_mask = city_mask[x];
        int right_mask = city_mask[y];

        if (left_mask & right_mask) {
            cout << y - x << '\n';
            continue;
        }

        long long answer = (long long)4e18;
        for (int mask = 0; mask < 16; ++mask) {
            if (!(mask & left_mask) || !(mask & right_mask) || positions[mask].empty()) {
                continue;
            }

            const vector<int> &v = positions[mask];
            auto it = lower_bound(v.begin(), v.end(), x);

            if (it != v.end() && *it <= y) {
                answer = y - x;
                break;
            }
            if (it != v.end()) {
                answer = min(answer, (long long)(y - x) + 2LL * (*it - y));
            }
            if (it != v.begin()) {
                --it;
                answer = min(answer, (long long)(y - x) + 2LL * (x - *it));
            }
        }

        if (answer == (long long)4e18) {
            cout << -1 << '\n';
        } else {
            cout << answer << '\n';
        }
    }
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

