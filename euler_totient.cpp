#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

///////////////////// start yanking ////////////////////
// single query (for n), TC: O(sqrt(n)), SC: O(1)
ll phi(ll n) {
    ll et = n;
    for (ll i = 2; i*i <= n; i++) {
        if (n%i == 0) {
            while (n%i == 0) {
                n /= i;
            }
            et -= et/i;
        }
    }
    if (n > 1) {
        et -= et/n;
    }
    return et;
}


// multiple queries (1 to n), TC: O(nloglogn) for precomputation, O(1) for query, SC: O(n)
const int N = 10000000;
ll phisieve[N+1] = {0};

void build_phi(ll n) { // call me (precomputation)
    for (int i = 1; i <= n; i++) {
        phisieve[i] = i;
    }
    for (ll i = 2; i <= n; i++) {
        if (phisieve[i] == i) {
            phisieve[i] = i-1;
            for (int j = i*2; j <= n; j += i) {
                phisieve[j] = (phisieve[j]/i)*(i-1);
            }
        }
    }
}

ll phi_q(ll n) { // call me (result)
    return phisieve[n];
}
///////////////////// stop yanking /////////////////////

int main() {
    ll n;
    cin >> n;
    cout << phi(n) << "\n";
    build_phi(n);
    for (int i = 1; i <=n; i++) {
        cout << phisieve[i] << " ";
    }
    cout << "\n";
    cin >> n;
    cout << phi_q(n);
    return 0;
}
