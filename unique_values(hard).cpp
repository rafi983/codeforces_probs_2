#include <iostream>
#include <vector>

using namespace std;

int query(const vector<int>& S) {
    if (S.empty()) return 0;
    cout << "? " << S.size();
    for (int v : S) cout << " " << v;
    cout << "\n";
    cout.flush();
    int res;
    cin >> res;
    if (res == -1) exit(0);
    return res;
}

void solve() {
    int n;
    if (!(cin >> n)) return;

    int total_n = 2 * n + 1;

    // Find z (the largest index)
    int L = 1, R = total_n;
    while (L < R) {
        int mid = L + (R - L) / 2;
        vector<int> S;
        for (int i = 1; i <= mid; i++) S.push_back(i);
        int A = query(S);
        if ((mid - A) % 2 != 0) {
            R = mid;
        } else {
            L = mid + 1;
        }
    }
    int z = L;

    // Find x (the smallest index)
    L = 1; R = z - 1;
    while (L < R) {
        int mid = L + (R - L + 1) / 2;
        vector<int> S;
        for (int i = mid; i <= total_n; i++) S.push_back(i);
        int A = query(S);
        int sz = total_n - mid + 1;
        if ((sz - A) % 2 != 0) {
            L = mid;
        } else {
            R = mid - 1;
        }
    }
    int x = L;

    // Find y (the middle index)
    L = x + 1; R = z - 1;
    while (L < R) {
        int mid = L + (R - L) / 2;
        vector<int> S;
        for (int i = 1; i <= mid; i++) S.push_back(i);
        S.push_back(z);
        int A = query(S);
        int sz = mid + 1;
        if ((sz - A) % 2 != 0) {
            R = mid;
        } else {
            L = mid + 1;
        }
    }
    int y = L;

    cout << "! " << x << " " << y << " " << z << "\n";
    cout.flush();
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
