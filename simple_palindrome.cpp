#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    string vowels = "aeiou";
    string ans;

    int base = n / 5;
    int extra = n % 5;

    for (int i = 0; i < 5; ++i) {
        ans.append(base + (i < extra), vowels[i]);
    }

    cout << ans << '\n';
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

