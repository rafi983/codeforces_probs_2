#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int query(const vector<int>& S) {
    if (S.empty()) return 0;
    cout << "? " << S.size();
    for (int x : S) cout << " " << x;
    cout << "\n";
    cout.flush();
    int res;
    cin >> res;
    if (res == -1) exit(0);
    return res;
}

int get_p(const vector<int>& S, int total_n) {
    if (S.empty()) return 0;
    if (S.size() == total_n) return 3;

    vector<int> Sc;
    vector<bool> in_S(total_n + 1, false);
    for (int x : S) in_S[x] = true;
    for (int i = 1; i <= total_n; i++) {
        if (!in_S[i]) Sc.push_back(i);
    }

    int a1 = query(S);
    int a2 = query(Sc);

    if (a1 > a2) return 1;
    if (a1 < a2) return 2;
    if ((S.size() - a1) % 2 != 0) return 3;
    return 0;
}

void solve() {
    int n;
    if (!(cin >> n)) return;

    int total_n = 2 * n + 1;
    vector<int> candidates(total_n);
    iota(candidates.begin(), candidates.end(), 1);

    vector<int> ans;

    auto find_one = [&](auto& self, const vector<int>& cands, int count) -> void {
        if (count == 0) return;
        if (cands.size() == count) {
            for (int x : cands) ans.push_back(x);
            return;
        }

        int mid = cands.size() / 2;
        vector<int> left(cands.begin(), cands.begin() + mid);
        vector<int> right(cands.begin() + mid, cands.end());

        int p_left = get_p(left, total_n);
        int p_right = count - p_left;

        if (p_left > 0) self(self, left, p_left);
        if (p_right > 0) self(self, right, p_right);
    };

    find_one(find_one, candidates, 3);

    cout << "! " << ans[0] << " " << ans[1] << " " << ans[2] << "\n";
    cout.flush();
}

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}

