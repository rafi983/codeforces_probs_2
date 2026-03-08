#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long count_covering_segments(int pos, int len, int k) {
    int left = max(0, pos - k + 1);
    int right = min(pos, len - k);
    return max(0, right - left + 1);
}

void print_int128(__int128 value) {
    if (value == 0) {
        cout << 0;
        return;
    }

    string s;
    while (value > 0) {
        s.push_back(char('0' + value % 10));
        value /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    int w;
    cin >> w;

    vector<long long> heights(w);
    for (int i = 0; i < w; ++i) {
        cin >> heights[i];
    }

    vector<long long> row_count(n), col_count(m);
    for (int i = 0; i < n; ++i) {
        row_count[i] = count_covering_segments(i, n, k);
    }
    for (int j = 0; j < m; ++j) {
        col_count[j] = count_covering_segments(j, m, k);
    }

    vector<long long> contribution;
    contribution.reserve(1LL * n * m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            contribution.push_back(row_count[i] * col_count[j]);
        }
    }

    sort(contribution.begin(), contribution.end(), greater<long long>());
    sort(heights.begin(), heights.end(), greater<long long>());

    __int128 answer = 0;
    for (int i = 0; i < w; ++i) {
        answer += (__int128) contribution[i] * heights[i];
    }

    print_int128(answer);
    cout << '\n';
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

