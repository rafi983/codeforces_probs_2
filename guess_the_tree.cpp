#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int ask(int a, int b) {
    cout << "? " << a << ' ' << b << endl;
    int x;
    cin >> x;
    if (x == -1) {
        exit(0);
    }
    return x;
}

void connect_node(int a, int b, vector<int>& known, vector<pair<int, int>>& edges) {
    if (known[b]) {
        return;
    }

    int mid = ask(a, b);
    if (mid == a) {
        known[b] = 1;
        edges.push_back({a, b});
        return;
    }

    if (!known[mid]) {
        connect_node(a, mid, known, edges);
    }
    connect_node(mid, b, known, edges);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> known(n + 1, 0);
        vector<pair<int, int>> edges;
        known[1] = 1;

        for (int v = 2; v <= n; ++v) {
            if (!known[v]) {
                connect_node(1, v, known, edges);
            }
        }

        cout << "!";
        for (auto [u, v] : edges) {
            cout << ' ' << u << ' ' << v;
        }
        cout << endl;
    }

    return 0;
}

