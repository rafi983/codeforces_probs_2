#include <iostream>
#include <set>
#include <vector>

using namespace std;

static const int MAX_VALUE = 2000000;
static const int START_LIMIT = MAX_VALUE + 1;
static const int SENTINEL = 4000005;
static const int SEG_SIZE = 1 << 21;

vector<int> segtree(SEG_SIZE * 2, 0);
vector<int> touched_nodes;

void set_gap_value(int start, int length) {
    int node = start + SEG_SIZE - 1;
    segtree[node] = length;
    touched_nodes.push_back(node);

    for (node >>= 1; node > 0; node >>= 1) {
        segtree[node] = max(segtree[node << 1], segtree[node << 1 | 1]);
        touched_nodes.push_back(node);
    }
}

int find_first_gap(int needed_length) {
    int node = 1;
    int left = 1;
    int right = SEG_SIZE;

    while (left < right) {
        int mid = (left + right) / 2;
        if (segtree[node << 1] >= needed_length) {
            node <<= 1;
            right = mid;
        } else {
            node = node << 1 | 1;
            left = mid + 1;
        }
    }

    return left;
}

void clear_segment_tree() {
    for (int node : touched_nodes) {
        segtree[node] = 0;
    }
    touched_nodes.clear();
}

void solve() {
    int n;
    cin >> n;

    set<int> present;
    present.insert(0);
    present.insert(SENTINEL);

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        present.insert(x);
    }

    int previous = *present.begin();
    for (auto it = next(present.begin()); it != present.end(); ++it) {
        int current = *it;
        int length = current - previous - 1;
        if (length > 0) {
            set_gap_value(previous + 1, length);
        }
        previous = current;
    }

    int m;
    cin >> m;

    vector<int> answers;
    answers.reserve(m);

    while (m--) {
        char type;
        int x;
        cin >> type >> x;

        if (type == '?') {
            answers.push_back(find_first_gap(x));
            continue;
        }

        if (type == '+') {
            auto next_it = present.lower_bound(x);
            int next_value = *next_it;
            int previous_value = *prev(next_it);

            set_gap_value(previous_value + 1, x - previous_value - 1);
            set_gap_value(x + 1, next_value - x - 1);
            present.insert(x);
        } else {
            auto it = present.find(x);
            int previous_value = *prev(it);
            int next_value = *next(it);

            set_gap_value(previous_value + 1, next_value - previous_value - 1);
            set_gap_value(x + 1, 0);
            present.erase(it);
        }
    }

    for (int i = 0; i < (int)answers.size(); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << answers[i];
    }
    cout << '\n';

    clear_segment_tree();
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

