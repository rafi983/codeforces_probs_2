#include <bits/stdc++.h>
using namespace std;

void solve() {
    int l, n, m;
    cin >> l >> n >> m;

    vector<int> a(l + 1);
    for (int i = 1; i <= l; ++i) {
        cin >> a[i];
    }

    vector<int> values = a;
    sort(values.begin() + 1, values.end());
    values.erase(unique(values.begin() + 1, values.end()), values.end());

    unordered_map<int, int> id;
    id.reserve(values.size() * 2 + 1);
    for (int i = 1; i < (int)values.size(); ++i) {
        id[values[i]] = i - 1;
    }

    vector<vector<int>> rowMax(max(1, (int)values.size() - 1), vector<int>(n + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int x;
            cin >> x;
            auto it = id.find(x);
            if (it != id.end()) {
                rowMax[it->second][i] = j;
            }
        }
    }

    vector<int> nextBest(n + 2, 0), curBest(n + 2, 0), down(n + 2, 0);

    for (int idx = l; idx >= 1; --idx) {
        down[n] = 0;
        for (int i = n - 1; i >= 1; --i) {
            down[i] = max(down[i + 1], nextBest[i + 1]);
        }

        const vector<int>& rows = rowMax[id[a[idx]]];
        for (int i = 1; i <= n; ++i) {
            curBest[i] = (rows[i] >= down[i] ? rows[i] : 0);
        }

        fill(nextBest.begin(), nextBest.end(), 0);
        swap(nextBest, curBest);
    }

    bool tsovakWins = false;
    for (int i = 1; i <= n; ++i) {
        if (nextBest[i] > 0) {
            tsovakWins = true;
            break;
        }
    }

    cout << (tsovakWins ? 'T' : 'N') << '\n';
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

