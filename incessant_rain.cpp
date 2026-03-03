#include <algorithm>
#include <iostream>
#include <random>
#include <set>
#include <vector>

using namespace std;

static const int NEG = -1000000000;

struct Agg {
    int sum;
    int pref;
    int suf;
    int best;
};

static Agg make_empty() {
    return {0, NEG, NEG, NEG};
}

static Agg make_single(int v) {
    return {v, v, v, v};
}

static Agg merge_agg(const Agg& a, const Agg& b) {
    Agg c;
    c.sum = a.sum + b.sum;
    c.pref = max(a.pref, a.sum + b.pref);
    c.suf = max(b.suf, b.sum + a.suf);
    c.best = max(max(a.best, b.best), a.suf + b.pref);
    return c;
}

struct Node {
    int key;
    int val;
    uint32_t prio;
    Node* l;
    Node* r;
    Agg agg;
};

struct NodePool {
    vector<Node> pool;
    mt19937 rng;

    NodePool() : rng(712367821u) {
        pool.reserve(2000000);
    }

    void reset() {
        pool.clear();
    }

    Node* make(int key, int val) {
        pool.push_back({key, val, rng(), nullptr, nullptr, make_single(val)});
        return &pool.back();
    }
};

static Agg get_agg(Node* t) {
    return t ? t->agg : make_empty();
}

static void pull(Node* t) {
    if (!t) return;
    Agg left = get_agg(t->l);
    Agg mid = make_single(t->val);
    Agg right = get_agg(t->r);
    t->agg = merge_agg(merge_agg(left, mid), right);
}

static void split_leq(Node* t, int key, Node*& a, Node*& b) {
    if (!t) {
        a = b = nullptr;
        return;
    }
    if (t->key <= key) {
        split_leq(t->r, key, t->r, b);
        a = t;
        pull(a);
    } else {
        split_leq(t->l, key, a, t->l);
        b = t;
        pull(b);
    }
}

static Node* merge_treap(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->prio > b->prio) {
        a->r = merge_treap(a->r, b);
        pull(a);
        return a;
    }
    b->l = merge_treap(a, b->l);
    pull(b);
    return b;
}

static void insert_or_assign(Node*& root, Node* item) {
    Node *a, *b, *c;
    split_leq(root, item->key, a, c);
    split_leq(a, item->key - 1, a, b);
    if (b) {
        b->val = item->val;
        pull(b);
        item = b;
    }
    root = merge_treap(merge_treap(a, item), c);
}

static void erase_key(Node*& root, int key) {
    Node *a, *b, *c;
    split_leq(root, key, a, c);
    split_leq(a, key - 1, a, b);
    // drop b
    root = merge_treap(a, c);
}

static int edge_val(int left_pos, int right_pos) {
    return 2 - (right_pos - left_pos);
}

class SegTreeMax {
public:
    SegTreeMax() : n(0) {}

    void init(int sz) {
        n = 1;
        while (n < sz) n <<= 1;
        t.assign(2 * n, 0);
    }

    void set_val(int pos, int val) {
        int p = pos + n;
        t[p] = val;
        p >>= 1;
        while (p) {
            t[p] = max(t[p << 1], t[p << 1 | 1]);
            p >>= 1;
        }
    }

    int all_max() const {
        return t[1];
    }

private:
    int n;
    vector<int> t;
};

struct ValueDS {
    set<int> pos;
    Node* edges = nullptr;
    int curM = 0;
};

static int compute_M(const ValueDS& ds) {
    if (ds.pos.empty()) return 0;
    int best_edges = ds.edges ? ds.edges->agg.best : NEG;
    if (best_edges < 0) best_edges = 0;
    return 1 + best_edges;
}

static void add_position(ValueDS& ds, int p, NodePool& pool) {
    auto it_succ = ds.pos.lower_bound(p);
    bool has_succ = (it_succ != ds.pos.end());
    bool has_pred = (it_succ != ds.pos.begin());

    int pred = -1, succ = -1;
    if (has_pred) {
        auto it_pred = it_succ;
        --it_pred;
        pred = *it_pred;
    }
    if (has_succ) succ = *it_succ;

    if (has_pred && has_succ) {
        erase_key(ds.edges, pred);
        insert_or_assign(ds.edges, pool.make(pred, edge_val(pred, p)));
        insert_or_assign(ds.edges, pool.make(p, edge_val(p, succ)));
    } else if (has_pred) {
        insert_or_assign(ds.edges, pool.make(pred, edge_val(pred, p)));
    } else if (has_succ) {
        insert_or_assign(ds.edges, pool.make(p, edge_val(p, succ)));
    }

    ds.pos.insert(p);
    ds.curM = compute_M(ds);
}

static void remove_position(ValueDS& ds, int p, NodePool& pool) {
    auto it = ds.pos.find(p);
    auto it_succ = it;
    ++it_succ;

    bool has_succ = (it_succ != ds.pos.end());
    bool has_pred = (it != ds.pos.begin());

    int pred = -1, succ = -1;
    if (has_pred) {
        auto it_pred = it;
        --it_pred;
        pred = *it_pred;
    }
    if (has_succ) succ = *it_succ;

    if (has_pred && has_succ) {
        erase_key(ds.edges, pred);
        erase_key(ds.edges, p);
        insert_or_assign(ds.edges, pool.make(pred, edge_val(pred, succ)));
    } else if (has_pred) {
        erase_key(ds.edges, pred);
    } else if (has_succ) {
        erase_key(ds.edges, p);
    }

    ds.pos.erase(it);
    ds.curM = compute_M(ds);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    NodePool pool;

    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];

        vector<ValueDS> ds(n + 1);
        pool.reset();

        for (int i = 1; i <= n; ++i) {
            add_position(ds[a[i]], i, pool);
        }

        SegTreeMax seg;
        seg.init(n + 1);
        for (int v = 1; v <= n; ++v) {
            seg.set_val(v, ds[v].curM);
        }

        for (int qi = 0; qi < q; ++qi) {
            int idx, x;
            cin >> idx >> x;

            int old = a[idx];
            if (old != x) {
                remove_position(ds[old], idx, pool);
                seg.set_val(old, ds[old].curM);

                add_position(ds[x], idx, pool);
                seg.set_val(x, ds[x].curM);

                a[idx] = x;
            }

            int bestM = seg.all_max();
            int ans = bestM / 2;
            cout << ans << (qi + 1 == q ? '\n' : ' ');
        }
    }

    return 0;
}

