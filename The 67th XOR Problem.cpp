#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX_NODES = 300005 * 31;
int trie[MAX_NODES][2];
int trie_cnt;
void insert(int num) {
    int curr = 0;
    for (int i = 29; i >= 0; --i) {
        int bit = (num >> i) & 1;
        if (trie[curr][bit] == 0) {
            trie[curr][bit] = ++trie_cnt;
            trie[trie_cnt][0] = trie[trie_cnt][1] = 0;
        }
        curr = trie[curr][bit];
    }
}
int getMaxXOR(int num) {
    int curr = 0;
    int maxXOR = 0;
    for (int i = 29; i >= 0; --i) {
        int bit = (num >> i) & 1;
        int toggledBit = 1 - bit;
        if (trie[curr][toggledBit]) {
            maxXOR |= (1 << i);
            curr = trie[curr][toggledBit];
        } else if (trie[curr][bit]) {
            curr = trie[curr][bit];
        } else {
            break;
        }
    }
    return maxXOR;
}
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    trie_cnt = 0;
    trie[0][0] = trie[0][1] = 0;
    int max_xor = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i > 0) {
            max_xor = max(max_xor, getMaxXOR(a[i]));
        }
        insert(a[i]);
    }
    cout << max_xor << "\n";
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
