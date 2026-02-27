#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int &x : a) cin >> x;

        vector<int> st;
        int roots = 0;
        for (int v : a) {
            while (!st.empty() && st.back() + 1 != v) st.pop_back();
            if (st.empty()) {
                ++roots;
            }
            st.push_back(v);
        }

        cout << roots;
        if (T) cout << '\n';
    }
    return 0;
}

