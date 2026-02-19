#include <iostream>
#include <string>

using namespace std;

void solve() {
    cout << 1 << endl;
    string response;
    cin >> response;

    if (response == "YES") {
        cout << 1 << endl;
    } else {

        cout << 2 << endl;
    }
}

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}

