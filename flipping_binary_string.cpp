#include <iostream>
#include <vector>
#include <string>

using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> s_val(n);
    for (int i = 0; i < n; ++i) {
        s_val[i] = s[i] - '0';
    }

    long long sum_x_0 = 0;
    vector<int> x_0(n);
    vector<int> indices_0;
    for(int i=0; i<n; ++i) {
        x_0[i] = s_val[i];
        sum_x_0 += x_0[i];
        if(x_0[i]) indices_0.push_back(i+1);
    }

    if (sum_x_0 % 2 == 0) {
        cout << indices_0.size() << endl;
        for (int i = 0; i < indices_0.size(); ++i) {
            cout << indices_0[i] << (i == indices_0.size() - 1 ? "" : " ");
        }
        cout << endl;
        return;
    }

    long long sum_x_1 = 0;
    vector<int> x_1(n);
    vector<int> indices_1;
    for(int i=0; i<n; ++i) {
        x_1[i] = 1 - s_val[i];
        sum_x_1 += x_1[i];
        if(x_1[i]) indices_1.push_back(i+1);
    }

    if (sum_x_1 % 2 == 1) {
        cout << indices_1.size() << endl;
        for (int i = 0; i < indices_1.size(); ++i) {
            cout << indices_1[i] << (i == indices_1.size() - 1 ? "" : " ");
        }
        cout << endl;
        return;
    }

    cout << -1 << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}