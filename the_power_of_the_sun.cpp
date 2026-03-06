#include <array>
#include <iostream>
#include <vector>

using namespace std;

static const int MOD = 998244353;
static const int MAX_A = 500000;
static const int FACT_10 = 3628800;
static const int FACT_11 = 39916800;
static const int FACT_12 = 479001600;
static const int FACTMOD_10 = 821984089;
static const int FACTMOD_11 = 644056242;
static const int FACTMOD_12 = 527656359;

struct Fenwick {
    int n = 0;
    vector<int> bit;

    explicit Fenwick(int size = 0) {
        init(size);
    }

    void init(int size) {
        n = size;
        bit.assign(n + 1, 0);
    }

    void add(int idx, int delta) {
        if (delta < 0) {
            delta += MOD;
        }
        for (int i = idx; i <= n; i += i & -i) {
            bit[i] += delta;
            if (bit[i] >= MOD) {
                bit[i] -= MOD;
            }
        }
    }

    int sum_prefix(int idx) const {
        int res = 0;
        for (int i = idx; i > 0; i -= i & -i) {
            res += bit[i];
            if (res >= MOD) {
                res -= MOD;
            }
        }
        return res;
    }

    int range_sum(int left, int right) const {
        int res = sum_prefix(right) - sum_prefix(left - 1);
        if (res < 0) {
            res += MOD;
        }
        return res;
    }
};

struct State {
    int type = 0;
    int value = 0;
};

vector<int> fact_mod;
const array<int, 13> small_fact = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};

int exact_factorial_mod(int x) {
    if (x <= MAX_A) {
        return fact_mod[x];
    }
    if (x == FACT_10) {
        return FACTMOD_10;
    }
    if (x == FACT_11) {
        return FACTMOD_11;
    }
    return FACTMOD_12;
}

bool is_active(const State& state) {
    if (state.type == 2) {
        return false;
    }
    if (state.type == 1) {
        return true;
    }
    return state.value != 1 && state.value != 2;
}

int find_next_active(int x, vector<int>& next_active) {
    if (next_active[x] == x) {
        return x;
    }
    return next_active[x] = find_next_active(next_active[x], next_active);
}

void advance_state(State& state) {
    if (state.type == 0) {
        int x = state.value;
        if (x <= 12) {
            state.value = small_fact[x];
            state.type = 0;
        } else {
            state.value = exact_factorial_mod(x);
            state.type = 1;
        }
    } else if (state.type == 1) {
        state.type = 2;
        state.value = 0;
    }
}

void solve() {
    int n, q;
    cin >> n >> q;

    vector<State> states(n + 1);
    Fenwick bit(n);
    vector<int> next_active(n + 2, n + 1);
    next_active[n + 1] = n + 1;

    for (int i = 1; i <= n; ++i) {
        int a;
        cin >> a;
        states[i] = {0, a};
        bit.add(i, a % MOD);
    }

    for (int i = n; i >= 1; --i) {
        next_active[i] = is_active(states[i]) ? i : next_active[i + 1];
    }

    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;

        if (type == 2) {
            cout << bit.range_sum(l, r) << '\n';
            continue;
        }

        int pos = find_next_active(l, next_active);
        while (pos <= r) {
            int old_value = states[pos].value;
            advance_state(states[pos]);
            int new_value = states[pos].value;
            bit.add(pos, new_value - old_value);

            int next_pos = find_next_active(pos + 1, next_active);
            if (!is_active(states[pos])) {
                next_active[pos] = next_pos;
            }
            pos = next_pos;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fact_mod.assign(MAX_A + 1, 1);
    for (int i = 1; i <= MAX_A; ++i) {
        fact_mod[i] = (long long)fact_mod[i - 1] * i % MOD;
    }

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

