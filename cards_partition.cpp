#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    long long k;
    cin >> n >> k;

    long long sum = 0;
    long long mx = 0;

    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        sum += x;
        mx = max(mx, x);
    }

    for (int deckSize = n; deckSize >= 1; --deckSize) {
        long long decks = max(mx, (sum + deckSize - 1) / deckSize);
        __int128 neededTotal = static_cast<__int128>(decks) * deckSize;
        if (neededTotal <= static_cast<__int128>(sum) + k) {
            cout << deckSize << '\n';
            return;
        }
    }
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

