#include <iostream>
#include <string>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        --p[i];
    }

    string s;
    cin >> s;

    vector<int> ans(n), visited(n, 0);

    for (int i = 0; i < n; ++i) {
        if (visited[i]) {
            continue;
        }

        vector<int> cycle;
        int cur = i;
        while (!visited[cur]) {
            visited[cur] = 1;
            cycle.push_back(cur);
            cur = p[cur];
        }

        int black_count = 0;
        for (int v : cycle) {
            if (s[v] == '0') {
                ++black_count;
            }
        }

        for (int v : cycle) {
            ans[v] = black_count;
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
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

