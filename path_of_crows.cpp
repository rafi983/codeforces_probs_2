#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge {
    int u, v;
};

struct Operation {
    int a, b, c;
};

vector<vector<int>> adj;
vector<int> p;
vector<Operation> ops;
int n;

bool findPath(int start, int end, vector<int>& path) {
    queue<int> q;
    q.push(start);
    vector<int> parent(n + 1, 0);
    vector<bool> visited(n + 1, false);
    visited[start] = true;

    bool found = false;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == end) {
            found = true;
            break;
        }

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    if (found) {
        int curr = end;
        while (curr != 0) {
            path.push_back(curr);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());
        return true;
    }
    return false;
}

void removeEdge(int u, int v) {
    auto& neighbors_u = adj[u];
    for (size_t i = 0; i < neighbors_u.size(); ++i) {
        if (neighbors_u[i] == v) {
            neighbors_u.erase(neighbors_u.begin() + i);
            break;
        }
    }
    auto& neighbors_v = adj[v];
    for (size_t i = 0; i < neighbors_v.size(); ++i) {
        if (neighbors_v[i] == u) {
            neighbors_v.erase(neighbors_v.begin() + i);
            break;
        }
    }
}

void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void solve() {
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    adj.assign(n + 1, vector<int>());
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ops.clear();


    for (int i = 0; i < n - 1; ++i) {
        int target = p[i];
        int current = p[i+1];

        vector<int> path;
        if (findPath(current, target, path)) {


            if (path.size() > 2) {


                for (size_t j = 1; j < path.size() - 1; ++j) {
                    int a = current;
                    int b = path[j];
                    int c = path[j+1];

                    ops.push_back({a, b, c});

                    removeEdge(a, b);
                    addEdge(a, c);
                }
            }
        }
    }

    cout << ops.size() << endl;
    for (const auto& op : ops) {
        cout << op.a << " " << op.b << " " << op.c << endl;
    }
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

