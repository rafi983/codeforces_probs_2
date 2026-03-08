#include <iostream>
#include <string>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        prefix[i + 1] = prefix[i] + x;
    }

    string s;
    cin >> s;

    int left = 0;
    int right = n - 1;
    long long answer = 0;

    while (true) {
        while (left < n && s[left] != 'L') {
            ++left;
        }
        while (right >= 0 && s[right] != 'R') {
            --right;
        }

        if (left >= right) {
            break;
        }

        answer += prefix[right + 1] - prefix[left];
        ++left;
        --right;
    }

    cout << answer << '\n';
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

