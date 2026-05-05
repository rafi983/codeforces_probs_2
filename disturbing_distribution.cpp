#include <iostream>
#include <vector>
using namespace std;

static const long long MOD = 676767677;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n + 1);
        long long sum_non_one = 0;
        int last_non_one = 0;

        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            if (a[i] > 1) {
                sum_non_one += a[i];
                last_non_one = i;
            }
        }

        bool need_one_chain = false;
        if (last_non_one == 0) {
            need_one_chain = true;
        } else {
            for (int i = last_non_one + 1; i <= n; ++i) {
                if (a[i] == 1) {
                    need_one_chain = true;
                    break;
                }
            }
        }

        long long ans = (sum_non_one + (need_one_chain ? 1 : 0)) % MOD;
        cout << ans << '\n';
    }

    return 0;
}
