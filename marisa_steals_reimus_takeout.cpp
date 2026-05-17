#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        int cnt[3] = {0, 0, 0};
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            ++cnt[x];
        }

        int answer = cnt[0];

        int c1 = cnt[1], c2 = cnt[2];
        int best = 0;
        int pairLimit = min(c1, c2);
        for (int pairs = 0; pairs <= pairLimit; ++pairs) {
            int cur = pairs + (c1 - pairs) / 3 + (c2 - pairs) / 3;
            best = max(best, cur);
        }

        answer += best;
        cout << answer << '\n';
    }

    return 0;
}
