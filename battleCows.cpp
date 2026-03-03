#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, q;
        cin >> n >> q;

        int N = 1 << n;
        vector<int> a(N + 1);
        for (int i = 1; i <= N; ++i) cin >> a[i];

        vector<int> seg(2 * N, 0);
        for (int i = 0; i < N; ++i) seg[N + i] = a[i + 1];
        for (int i = N - 1; i >= 1; --i) seg[i] = seg[i << 1] ^ seg[i << 1 | 1];

        while (q--) {
            int b, c;
            cin >> b >> c;

            int delta = a[b] ^ c;
            long long above = 0;

            int node = N + (b - 1);
            int childSize = 1;

            while (node > 1) {
                int parent = node >> 1;
                int left = parent << 1;
                int right = left | 1;

                bool inLeft = (node == left);
                int xLeft = seg[left] ^ (inLeft ? delta : 0);
                int xRight = seg[right] ^ (inLeft ? 0 : delta);

                bool leftWins = (xLeft >= xRight);

                if (inLeft) {
                    if (!leftWins) above += childSize;
                } else {
                    if (leftWins) above += childSize;
                }

                node = parent;
                childSize <<= 1;
            }

            cout << above << '\n';
        }
    }

    return 0;
}

