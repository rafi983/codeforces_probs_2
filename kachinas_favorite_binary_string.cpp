#include <iostream>
#include <string>
using namespace std;

int ask(int l, int r) {
    cout << "? " << l << ' ' << r << endl;
    int value;
    cin >> value;
    if (value == -1) {
        exit(0);
    }
    return value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        int first_positive = -1;
        int prefix_value = 0;
        for (int i = 2; i <= n; ++i) {
            prefix_value = ask(1, i);
            if (prefix_value > 0) {
                first_positive = i;
                break;
            }
        }

        if (first_positive == -1) {
            cout << "! IMPOSSIBLE" << endl;
            continue;
        }

        string s(n, '?');
        int zeros = prefix_value;
        int ones = first_positive - 1 - zeros;

        for (int i = 0; i < ones; ++i) {
            s[i] = '1';
        }
        for (int i = ones; i < first_positive - 1; ++i) {
            s[i] = '0';
        }
        s[first_positive - 1] = '1';

        int current = prefix_value;
        for (int i = first_positive + 1; i <= n; ++i) {
            int next = ask(1, i);
            if (next == current) {
                s[i - 1] = '0';
                ++zeros;
            } else {
                s[i - 1] = '1';
            }
            current = next;
        }

        cout << "! " << s << endl;
    }

    return 0;
}
