#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

struct Candidate {
    int d;
    int u;
    int v;
    vector<int> path;
};

struct CandidateCmp {
    bool operator()(const Candidate& a, const Candidate& b) const {
        if (a.d != b.d) return a.d < b.d;
        if (a.u != b.u) return a.u < b.u;
        return a.v < b.v;
    }
};

class Solver {
public:
    explicit Solver(int n) : n(n), g(n + 1), removed(n + 1, 0), distA(n + 1, -1), distB(n + 1, -1), parentFromU(n + 1, -1) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> solve() {
        priority_queue<Candidate, vector<Candidate>, CandidateCmp> pq;
        if (n >= 1) {
            pq.push(analyze_component(1));
        }

        vector<int> answer;
        answer.reserve(3 * n);

        while (!pq.empty()) {
            Candidate cur = pq.top();
            pq.pop();

            answer.push_back(cur.d);
            answer.push_back(cur.u);
            answer.push_back(cur.v);

            for (int x : cur.path) {
                removed[x] = 1;
            }

            for (int x : cur.path) {
                for (int nei : g[x]) {
                    if (!removed[nei]) {
                        pq.push(analyze_component(nei));
                    }
                }
            }
        }

        return answer;
    }

private:
    int n;
    vector<vector<int>> g;
    vector<char> removed;
    vector<int> distA;
    vector<int> distB;
    vector<int> parentFromU;

    pair<int, int> farthest_no_parent(int src) {
        pair<int, int> best = {-1, -1};
        vector<tuple<int, int, int>> st;
        st.reserve(64);
        st.push_back({src, 0, -1});

        while (!st.empty()) {
            auto [u, d, p] = st.back();
            st.pop_back();

            if (d > best.first || (d == best.first && u > best.second)) {
                best = {d, u};
            }

            for (int v : g[u]) {
                if (v == p || removed[v]) continue;
                st.push_back({v, d + 1, u});
            }
        }

        return best;
    }

    pair<int, int> farthest_with_parent(int src) {
        pair<int, int> best = {-1, -1};
        vector<tuple<int, int, int>> st;
        st.reserve(64);
        st.push_back({src, 0, -1});

        while (!st.empty()) {
            auto [u, d, p] = st.back();
            st.pop_back();
            parentFromU[u] = p;

            if (d > best.first || (d == best.first && u > best.second)) {
                best = {d, u};
            }

            for (int v : g[u]) {
                if (v == p || removed[v]) continue;
                st.push_back({v, d + 1, u});
            }
        }

        return best;
    }

    vector<int> fill_dist(int src, vector<int>& dist) {
        vector<int> nodes;
        vector<pair<int, int>> st;
        st.reserve(64);
        st.push_back({src, -1});
        dist[src] = 0;

        while (!st.empty()) {
            auto [u, p] = st.back();
            st.pop_back();
            nodes.push_back(u);

            for (int v : g[u]) {
                if (v == p || removed[v]) continue;
                dist[v] = dist[u] + 1;
                st.push_back({v, u});
            }
        }

        return nodes;
    }

    Candidate analyze_component(int start) {
        auto p1 = farthest_no_parent(start);
        int A = p1.second;

        auto p2 = farthest_no_parent(A);
        int L = p2.first;
        int B = p2.second;

        vector<int> nodes = fill_dist(A, distA);
        fill_dist(B, distB);

        int u = -1;
        for (int x : nodes) {
            if (max(distA[x], distB[x]) == L && x > u) {
                u = x;
            }
        }

        auto p3 = farthest_with_parent(u);
        int v = p3.second;

        vector<int> path;
        for (int cur = v; cur != -1; cur = parentFromU[cur]) {
            path.push_back(cur);
            if (cur == u) break;
        }

        for (int x : nodes) {
            distA[x] = -1;
            distB[x] = -1;
            parentFromU[x] = -1;
        }

        return Candidate{L + 1, u, v, move(path)};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        Solver solver(n);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            solver.add_edge(u, v);
        }

        vector<int> ans = solver.solve();
        for (int x : ans) {
            cout << x << ' ';
        }
        cout << '\n';
    }

    return 0;
}

