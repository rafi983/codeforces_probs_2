#include <iostream>
#include <vector>

using namespace std;

const int MAX_P = 200000;
vector<long long> primes;
bool is_prime[MAX_P];

void sieve() {
    fill(is_prime, is_prime + MAX_P, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p < MAX_P; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i < MAX_P; i += p)
                is_prime[i] = false;
        }
    }
    for (int p = 2; p < MAX_P; p++) {
        if (is_prime[p]) primes.push_back(p);
    }
}

void solve() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << primes[i] * primes[i + 1] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}