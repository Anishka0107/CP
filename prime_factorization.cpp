#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(sqrt(n))

///////////////////// start yanking ////////////////////
// prime factorization, single query, TC: O(sqrt(n)), SC: O()
vector<ll> prime_factors;

void prime_factorization(ll n) {
    while (n%2 == 0) {
        prime_factors.push_back(2);
        n /= 2;
    }
    for (int i = 3; i <= sqrt(n); i += 2) {
        while (n%i == 0) {
            prime_factors.push_back(i);
            n /= i;
        }
    }
    if (n > 2) {
        prime_factors.push_back(n);
    }
}


// multiple queries using sieve, TC: O(log(n)) per query, O(n) for sieve computation, SC: O(n)
const int N = 10000000;
vector<int> primes;
int mpf[N+1]; // minimum prime factor

void build_sieve() { // call me (precomputation)
    for (int i = 2; i <= N; i++) {
        if (mpf[i] == 0) {
            primes.push_back(i);
            mpf[i] = i;
        }
        for (int j = 0; j < primes.size() && i*primes[j] <= N && primes[j] <= mpf[i]; j++) {
            mpf[i*primes[j]] = primes[j];
        }
    }
}

vector<int> prime_factorization_q(int n) { // call me (result)
    vector<int> pf;
    while (n > 1) {
        pf.push_back(mpf[n]);
        n /= mpf[n];
    }
    return pf;
}
///////////////////// stop yanking /////////////////////

int main() {
    ll n;
    cin >> n;
    prime_factorization(n);
    for (int i = 0; i < prime_factors.size(); i++) {
        cout << prime_factors[i] << " ";
    }
    cout << "\n";
    ll q;
    cin >> q;
    build_sieve();
    while (q--) {
        cin >> n;
        auto y = prime_factorization_q(n);
        for (auto & yy : y) {
            cout << yy << " ";
        }
        cout << "\n";
    }
    return 0;
}
