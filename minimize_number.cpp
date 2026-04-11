#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int operations = 0;
    while (true) {
        bool all_even = true;
        for (int x : a) {
            if (x % 2 != 0) {
                all_even = false;
                break;
            }
        }

        if (all_even) {
            for (int& x : a) {
                x /= 2;
            }
            operations++;
        } else {
            break;
        }
    }

    cout << operations << "\n";
    return 0;
}
