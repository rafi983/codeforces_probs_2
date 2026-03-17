#include <bits/stdc++.h>
using namespace std;

static int digit_sum_int(int x) {
    int s = 0;
    while (x > 0) {
        s += x % 10;
        x /= 10;
    }
    return s;
}

static string build_tail(int first_sum, array<int, 10> &tail_cnt, int &tail_sum_digits) {
    string tail;
    tail_cnt.fill(0);
    tail_sum_digits = 0;

    int cur = first_sum;
    while (true) {
        string part = to_string(cur);
        tail += part;
        for (char ch : part) {
            int d = ch - '0';
            ++tail_cnt[d];
            tail_sum_digits += d;
        }
        if (cur <= 9) break;
        cur = digit_sum_int(cur);
    }
    return tail;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        string s;
        cin >> s;

        int n = (int)s.size();
        array<int, 10> cnt{};
        cnt.fill(0);
        int total_sum = 0;
        for (char ch : s) {
            int d = ch - '0';
            ++cnt[d];
            total_sum += d;
        }

        if (n == 1 && s[0] != '0') {
            cout << s << '\n';
            continue;
        }

        bool found = false;

        for (int first_sum = 1; first_sum <= 9 * n && !found; ++first_sum) {
            array<int, 10> tail_cnt;
            int tail_sum_digits = 0;
            string tail = build_tail(first_sum, tail_cnt, tail_sum_digits);

            if ((int)tail.size() >= n) continue;

            bool ok = true;
            for (int d = 0; d <= 9; ++d) {
                if (tail_cnt[d] > cnt[d]) {
                    ok = false;
                    break;
                }
            }
            if (!ok) continue;

            array<int, 10> rem = cnt;
            for (int d = 0; d <= 9; ++d) rem[d] -= tail_cnt[d];

            int rem_len = n - (int)tail.size();
            int rem_sum = total_sum - tail_sum_digits;

            if (rem_len < 2) continue;
            if (rem_sum != first_sum) continue;

            int first_digit = -1;
            for (int d = 1; d <= 9; ++d) {
                if (rem[d] > 0) {
                    first_digit = d;
                    break;
                }
            }
            if (first_digit == -1) continue;

            string x0;
            x0.reserve(rem_len);
            x0.push_back(char('0' + first_digit));
            --rem[first_digit];
            for (int d = 0; d <= 9; ++d) {
                x0.append(rem[d], char('0' + d));
            }

            cout << x0 << tail << '\n';
            found = true;
        }

        if (!found) {
            cout << s << '\n';
        }
    }

    return 0;
}

