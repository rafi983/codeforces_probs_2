#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int to;
    int bus;
    int walk;
};

long long t0_time, t1_time, t2_time;
vector<vector<Edge>> graph;

long long next_arrival(long long current_time, int bus_time, int walk_time) {
    long long best = current_time + walk_time;

    if (current_time + bus_time <= t1_time) {
        best = min(best, current_time + bus_time);
    } else if (current_time <= t2_time) {
        best = min(best, t2_time + (long long) bus_time);
    } else {
        best = min(best, current_time + bus_time);
    }

    return best;
}

bool can_arrive(long long start_time) {
    const long long INF = numeric_limits<long long>::max() / 4;
    int n = (int) graph.size() - 1;

    vector<long long> dist(n + 1, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist[1] = start_time;
    pq.push({start_time, 1});

    while (!pq.empty()) {
        auto [current_time, node] = pq.top();
        pq.pop();

        if (current_time != dist[node]) {
            continue;
        }
        if (current_time > t0_time) {
            continue;
        }
        if (node == n) {
            return true;
        }

        for (const Edge &edge : graph[node]) {
            long long arrival = next_arrival(current_time, edge.bus, edge.walk);
            if (arrival < dist[edge.to] && arrival <= t0_time) {
                dist[edge.to] = arrival;
                pq.push({arrival, edge.to});
            }
        }
    }

    return dist[n] <= t0_time;
}

void solve() {
    int n, m;
    cin >> n >> m;
    cin >> t0_time >> t1_time >> t2_time;

    graph.assign(n + 1, {});
    for (int i = 0; i < m; ++i) {
        int u, v, bus_time, walk_time;
        cin >> u >> v >> bus_time >> walk_time;
        graph[u].push_back({v, bus_time, walk_time});
        graph[v].push_back({u, bus_time, walk_time});
    }

    if (!can_arrive(0)) {
        cout << -1 << '\n';
        return;
    }

    long long left = 0;
    long long right = t0_time;
    while (left < right) {
        long long mid = left + (right - left + 1) / 2;
        if (can_arrive(mid)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    cout << left << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

