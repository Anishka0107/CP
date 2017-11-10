#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

///////////////////// start yanking ////////////////////
vector<ll> primes;
vector<bool> segsieve;

void build_segsieve(ll b, ll e) {
    assert(b <= e && b >= 0);
    segsieve.assign(e-b+1, true);
    for (ll i = 2; i*i <= e; i++) {
        for (ll j = max(i*i, (b+(i-1))/i*i); j <= e; j += i) {
            segsieve[j-b] = false;
        }
    }
    if (b == 0) {
        segsieve[0] = segsieve[1] = 0;
    } else if (b == 1) {
        segsieve[0] = 0;
    }
    for (ll i = 0; i <= e-b; i++) {
        if (segsieve[i]) {
            primes.push_back(i+b);
        }
    }
}
///////////////////// stop yanking /////////////////////

int main() {
    ll b, e;
    cin >> b >> e;
    build_segsieve(b, e);
    for (ll i = 0; i < primes.size(); i++) { 
        cout << primes[i] << " ";
    }
    cout << "\n";
    int n;
    cin >> n;
    cout << segsieve[n-b];
    return 0;
}
