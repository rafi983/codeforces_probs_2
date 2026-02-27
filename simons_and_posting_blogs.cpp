#include <bits/stdc++.h>
using namespace std;

static bool lex_less(const vector<int>& a, const vector<int>& b) {
    size_t i = 0;
    while (i < a.size() && i < b.size()) {
        if (a[i] != b[i]) return a[i] < b[i];
        ++i;
    }
    return a.size() < b.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<int>> blogs(n);
        for (int i = 0; i < n; ++i) {
            int li;
            cin >> li;
            blogs[i].resize(li);
            for (int j = 0; j < li; ++j) cin >> blogs[i][j];
        }

        vector<vector<int>> uniq_rev(n);
        uniq_rev.reserve(n);
        for (int i = 0; i < n; ++i) {
            unordered_set<int> seen_local;
            seen_local.reserve(blogs[i].size() * 2 + 1);
            for (int j = (int)blogs[i].size() - 1; j >= 0; --j) {
                int v = blogs[i][j];
                if (seen_local.insert(v).second) {
                    uniq_rev[i].push_back(v);
                }
            }
        }

        vector<int> result;
        result.reserve(3000);
        vector<char> used(n, 0);
        unordered_set<int> seen_global;
        seen_global.reserve(6001);

        int remaining = n;
        while (remaining > 0) {
            int best_idx = -1;
            vector<int> best_contrib;

            for (int i = 0; i < n; ++i) {
                if (used[i]) continue;
                vector<int> contrib;
                contrib.reserve(uniq_rev[i].size());
                for (int v : uniq_rev[i]) {
                    if (seen_global.find(v) == seen_global.end()) {
                        contrib.push_back(v);
                    }
                }
                if (best_idx == -1 || lex_less(contrib, best_contrib)) {
                    best_idx = i;
                    best_contrib.swap(contrib);
                }
            }

            used[best_idx] = 1;
            --remaining;
            for (int v : best_contrib) {
                result.push_back(v);
                seen_global.insert(v);
            }
        }

        for (size_t i = 0; i < result.size(); ++i) {
            if (i) cout << ' ';
            cout << result[i];
        }
        cout << '\n';
    }

    return 0;
}
