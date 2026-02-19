#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;
    int winner_index = -1;
    int max_quality = -1;

    for (int i = 1; i <= n; ++i) {
        int a, b;
        cin >> a >> b;
        if (a <= 10) {
            if (b > max_quality) {
                max_quality = b;
                winner_index = i;
            }
        }
    }
    cout << winner_index << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
