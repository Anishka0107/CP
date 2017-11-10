#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(log(e))

///////////////////// start yanking ////////////////////
ll modpow(ll b, ll e, ll m) {
    ll result = 1;
    while (e > 0) {
        if (e & 1) {
            result = (result * b) % m;
        }
        e >>= 1;
        b = (b * b) % m;
    }
    return result;
}
///////////////////// stop yanking /////////////////////

int main() {
    ll b, e, m;
    cin >> b >> e >> m;
    cout << modpow(b, e, m);
    return 0;
}
