#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;

        vector<int> freq(26, 0);
        for (char c : s) {
            ++freq[c - 'a'];
        }

        vector<pair<int, char>> letters;
        letters.reserve(26);
        for (int i = 0; i < 26; ++i) {
            if (freq[i] > 0) {
                letters.push_back({freq[i], static_cast<char>('a' + i)});
            }
        }

        sort(letters.begin(), letters.end());

        string ans;
        ans.reserve(n);

        while (true) {
            bool added = false;
            for (auto &entry : letters) {
                if (entry.first > 0) {
                    ans.push_back(entry.second);
                    --entry.first;
                    added = true;
                }
            }
            if (!added) {
                break;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}

