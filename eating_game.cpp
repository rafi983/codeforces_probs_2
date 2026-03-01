#include <iostream>
#include <vector>
#include <numeric>
#include <set>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    int sum_a = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum_a += a[i];
    }

    set<int> winners;

    for (int start_player = 0; start_player < n; ++start_player) {
        vector<int> current_a = a;
        int current_sum = sum_a;
        int current_player = start_player;
        int last_eater = -1;

        while (current_sum > 0) {
            if (current_a[current_player] > 0) {
                current_a[current_player]--;
                current_sum--;
                last_eater = current_player;
            }
            current_player = (current_player + 1) % n;
        }
        if (last_eater != -1) {
            winners.insert(last_eater);
        }
    }

    cout << winners.size() << endl;
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

