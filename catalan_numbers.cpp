#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

///////////////////// start yanking ////////////////////
// single query, TC: O(n), SC: O(1)
ll C(ll n, ll k) {
    ll result = 1;
    k = (k > n-k) ? (n-k) : k;
    for (ll i = 0; i < k; i++) {
        result *= (n-i);
        result /= (i+1);    
    }
    return result;
}

ll get_catalan(ll n) { // call me (result)
    return C(2*n, n) / (n+1);
}

// multiple queries, TC: O(n*n) for precomputation, O(1) for query, SC: O(n)
const int N = 10000000;
ll catalan[N+1];

void calculate_catalan(ll n, ll mod) { // call me (precomputation)
    catalan[0] = catalan[1] = 1;
    for (ll i = 2; i <= n; i++) {
        for (ll j = 0; j < i; j++) {
            catalan[i] = (catalan[i] + (catalan[j] * catalan[i-j-1]) % mod) % mod;
        }
    }
}

ll get_catalan_q(ll n) { // call me result
    return catalan[n];
}
///////////////////// stop yanking /////////////////////

int main() {
    ll n;
    cin >> n;
    cout << get_catalan(n) << "\n";
    ll mod;
    cin >> mod;
    calculate_catalan(n, mod);
    for (ll i = 0; i <= n; i++) {
        cout << catalan[i] << " ";
    }
    cout << "\n";
    cin >> n;
    cout << get_catalan_q(n);
    return 0;
}
