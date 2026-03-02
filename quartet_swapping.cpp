#include <bits/stdc++.h>
using namespace std;

static int permutation_parity(const vector<int>& original, const vector<int>& sorted, int maxValue) {
    int m = static_cast<int>(original.size());
    vector<int> rank(maxValue + 1, -1);
    for (int i = 0; i < m; ++i) {
        rank[sorted[i]] = i;
    }
    vector<int> perm(m);
    for (int i = 0; i < m; ++i) {
        perm[i] = rank[original[i]];
    }

    vector<int> visited(m, 0);
    int cycles = 0;
    for (int i = 0; i < m; ++i) {
        if (visited[i]) continue;
        int cur = i;
        while (!visited[cur]) {
            visited[cur] = 1;
            cur = perm[cur];
        }
        ++cycles;
    }
    return (m - cycles) % 2;
}

static vector<int> build_answer(const vector<int>& group0, const vector<int>& group1, int n) {
    vector<int> ans(n);
    int i0 = 0, i1 = 0;
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            ans[i] = group0[i0++];
        } else {
            ans[i] = group1[i1++];
        }
    }
    return ans;
}

static void swap_last_two(vector<int>& v) {
    int m = static_cast<int>(v.size());
    if (m >= 2) {
        swap(v[m - 2], v[m - 1]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 0;
    if (!(cin >> t)) return 0;
    while (t--) {

        int n = 0;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        vector<int> group0_orig;
        vector<int> group1_orig;
        group0_orig.reserve((n + 1) / 2);
        group1_orig.reserve(n / 2);

        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) group0_orig.push_back(a[i]);
            else group1_orig.push_back(a[i]);
        }

        vector<int> group0_sorted = group0_orig;
        vector<int> group1_sorted = group1_orig;
        sort(group0_sorted.begin(), group0_sorted.end());
        sort(group1_sorted.begin(), group1_sorted.end());

        int parity0 = permutation_parity(group0_orig, group0_sorted, n);
        int parity1 = permutation_parity(group1_orig, group1_sorted, n);

        vector<int> answer;
        if (parity0 == parity1) {
            answer = build_answer(group0_sorted, group1_sorted, n);
        } else {
            vector<int> group1_flip = group1_sorted;
            vector<int> group0_flip = group0_sorted;
            swap_last_two(group1_flip);
            swap_last_two(group0_flip);

            vector<int> cand1 = build_answer(group0_sorted, group1_flip, n);
            vector<int> cand2 = build_answer(group0_flip, group1_sorted, n);

            answer = (cand1 < cand2) ? cand1 : cand2;
        }

        for (int i = 0; i < n; ++i) {
            cout << answer[i] << (i + 1 == n ? '\n' : ' ');
        }
    }
    return 0;
}
