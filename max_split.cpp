#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (cin >> s) {
        int balance = 0;
        vector<string> ans;
        string curr = "";

        for (char c : s) {
            curr += c;
            if (c == 'L') {
                balance++;
            } else {
                balance--;
            }

            if (balance == 0) {
                ans.push_back(curr);
                curr = "";
            }
        }

        cout << ans.size() << "\n";
        for (const string& res : ans) {
            cout << res << "\n";
        }
    }
    return 0;
}
