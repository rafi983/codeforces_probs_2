#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int k;
        cin >> k;

        vector<int> cnt(k + 1, 0);
        for (int i = 0; i < k; ++i) {
            int x;
            cin >> x;
            ++cnt[x];
        }

        int target = k - 2;
        for (int d = 1; d * d <= target; ++d) {
            if (target % d != 0) {
                continue;
            }

            int other = target / d;
            if (d == other) {
                if (cnt[d] >= 2) {
                    cout << d << ' ' << other << '\n';
                    break;
                }
            } else if (cnt[d] > 0 && other <= k && cnt[other] > 0) {
                cout << d << ' ' << other << '\n';
                break;
            }
        }
    }

    return 0;
}

