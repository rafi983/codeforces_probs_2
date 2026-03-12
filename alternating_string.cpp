#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    if (n % 2 == 0) {
        vector<vector<int>> cnt(2, vector<int>(26, 0));
        for (int i = 0; i < n; ++i) {
            cnt[i % 2][s[i] - 'a']++;
        }

        int best_even = 0;
        int best_odd = 0;
        for (int c = 0; c < 26; ++c) {
            best_even = max(best_even, cnt[0][c]);
            best_odd = max(best_odd, cnt[1][c]);
        }

        cout << n - best_even - best_odd << '\n';
        return;
    }

    vector<vector<int>> left(2, vector<int>(26, 0));
    vector<vector<int>> right(2, vector<int>(26, 0));

    for (int i = 0; i < n; ++i) {
        right[i % 2][s[i] - 'a']++;
    }

    int answer = n;
    for (int i = 0; i < n; ++i) {
        int current = s[i] - 'a';
        right[i % 2][current]--;

        int best_even = 0;
        int best_odd = 0;
        for (int c = 0; c < 26; ++c) {
            best_even = max(best_even, left[0][c] + right[1][c]);
            best_odd = max(best_odd, left[1][c] + right[0][c]);
        }

        answer = min(answer, n - best_even - best_odd);
        left[i % 2][current]++;
    }

    cout << answer << '\n';
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

