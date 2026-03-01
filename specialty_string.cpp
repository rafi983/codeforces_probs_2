#include <bits/stdc++.h>
using namespace std;

static bool can_win(const string& s) {

    string st;
    st.reserve(s.size());

    for (char ch : s) {
        if (!st.empty() && st.back() == ch) {
            st.pop_back();
        } else {
            st.push_back(ch);
        }
    }
    return st.empty();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 0;
    if (!(cin >> t)) {
        return 0;
    }
    while (t--) {
        int n = 0;
        string s;
        cin >> n >> s;
        (void)n;
        cout << (can_win(s) ? "YES" : "NO") << "\n";
    }
    return 0;
}
