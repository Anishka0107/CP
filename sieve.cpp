#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(n) // not the traditional sieve of eratosthenes (O(n*log(log(n)))), requires memory

///////////////////// start yanking ////////////////////
const int N = 10000000;
vector<int> primes;
vector<bool> sieve(N+1, true);
int mpf[N+1]; // minimum prime factor

void build_sieve() { // call me (precomputation)
    sieve[0] = 0, sieve[1] = 0;
    for (int i = 2; i <= N; i++) {
        if (sieve[i]) {
            primes.push_back(i);
            mpf[i] = i;
        }
        for (int j = 0; j < primes.size() && i*primes[j] <= N && primes[j] <= mpf[i]; j++) {
            mpf[i*primes[j]] = primes[j];
            sieve[i*primes[j]] = false;
        }
    }
}

bool is_prime(int n) { // call me (result)
    assert(n < N && n > 0);
    return sieve[n];
}
///////////////////// stop yanking /////////////////////

int main() {
    build_sieve();
    for (int i = 0; i < primes.size(); i++) { 
        cout << primes[i] << " ";
    }
    cout << "\n";
    int n;
    cin >> n;
    cout << is_prime(n);
    return 0;
}
