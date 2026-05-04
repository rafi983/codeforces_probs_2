#include <bits/stdc++.h>
using namespace std;

void solve(istream& in, ostream& out) {
    int t;
    if (!(in >> t)) {
        return;
    }
    while (t--) {
        int n;
        in >> n;
        vector<long long> a6, a2, a3, a1;
        a6.reserve(n);
        a2.reserve(n);
        a3.reserve(n);
        a1.reserve(n);
        for (int i = 0; i < n; ++i) {
            long long x;
            in >> x;
            if (x % 6 == 0) {
                a6.push_back(x);
            } else if (x % 2 == 0) {
                a2.push_back(x);
            } else if (x % 3 == 0) {
                a3.push_back(x);
            } else {
                a1.push_back(x);
            }
        }

        bool first = true;
        auto emit = [&](const vector<long long>& v) {
            for (long long x : v) {
                if (!first) out << ' ';
                out << x;
                first = false;
            }
        };

        emit(a6);
        emit(a2);
        emit(a1);
        emit(a3);
        out << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve(cin, cout);
    return 0;
}

