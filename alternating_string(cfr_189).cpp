#include <iostream>
#include <string>

using namespace std;

static bool canMatchPattern(const string& s, char first) {
    int n = (int)s.size();
    int firstMismatch = -1;
    int lastMismatch = -1;
    int mismatchCount = 0;

    for (int i = 0; i < n; ++i) {
        char expected = (i % 2 == 0 ? first : (first == 'a' ? 'b' : 'a'));
        if (s[i] != expected) {
            if (firstMismatch == -1) {
                firstMismatch = i;
            }
            lastMismatch = i;
            ++mismatchCount;
        }
    }

    if (mismatchCount == 0) {
        return true;
    }

    return mismatchCount == lastMismatch - firstMismatch + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        string s;
        cin >> s;

        bool ok = canMatchPattern(s, 'a') || canMatchPattern(s, 'b');
        cout << (ok ? "YES" : "NO") << '\n';
    }

    return 0;
}

