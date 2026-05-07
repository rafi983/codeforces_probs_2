#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<long long> a(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];

        long long best_value = a[n];
        int answer = (a[n] > 0 ? 1 : 0);

        for (int i = n - 1; i >= 1; --i) {
            long long c1 = a[i];
            long long c2 = a[i] + a[i + 1];
            long long c3 = a[i] + best_value;
            long long cur_best = max(c1, max(c2, c3));

            if (cur_best > 0) ++answer;
            best_value = cur_best;
        }

        cout << answer << '\n';
    }

    return 0;
}
