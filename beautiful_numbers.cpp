#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

long long sum_digits(long long n) {
    long long sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

bool is_beautiful(long long n) {
    long long s = sum_digits(n);
    return sum_digits(s) == s;
}

void solve() {
    string x_str;
    cin >> x_str;
    int n = x_str.length();

    vector<int> digits(n);
    long long current_digit_sum = 0;
    for(int i=0; i<n; ++i) {
        digits[i] = x_str[i] - '0';
        current_digit_sum += digits[i];
    }

    long long sum_of_sum = sum_digits(current_digit_sum);
    if (sum_of_sum == current_digit_sum) {
        cout << 0 << endl;
        return;
    }


    if (n == 1) {
        cout << 0 << endl;
        return;
    }

    vector<int> reductions;
    reductions.push_back(digits[0] - 1);
    for(int i=1; i<n; ++i) {
        reductions.push_back(digits[i]);
    }

    sort(reductions.rbegin(), reductions.rend());

    long long needed_reduction = current_digit_sum - 9;
    if (needed_reduction <= 0) {
        cout << 0 << endl;
        return;
    }

    long long current_reduction = 0;
    int moves = 0;
    for(int red : reductions) {
        current_reduction += red;
        moves++;
        if (current_reduction >= needed_reduction) {
            cout << moves << endl;
            return;
        }
    }

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

