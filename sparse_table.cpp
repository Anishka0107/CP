#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Range GCD Query
// For range queries without updates
// TC: O(n*log(n)) or more for precomputation, O(log(n)) or O(func) per query depending on query type, SC: O(n*log(n))
// Note: Queries where the number of times an element is present does not matter, can be answered in O(func) time
// Example: RMQ takes O(1) time per query, GCD takes O(log(n)) time per query (reason - gcd calculation)
// Note: Not useful for range sum (takes O(log(n)) time per query (reason - calculation itself)) or similar, expept for simplicity reasons. Use segtree or prefix sum etc.

///////////////////// start yanking ////////////////////
const ll N = 1000007, K = floor(log2(N));
ll arr[N], st[N][K+1], logt[N];

void build(ll n) { // call me (precomputation)
    logt[1] = 0;
    for (ll i = 2; i <= n; i++) {
        logt[i] = logt[i/2] + 1;
    }
    for (ll i = 0; i < n; i++) {
        st[i][0] = arr[i];
    }
    for (ll j = 1; j <= K; j++) {
        for (ll i = 0; i+(1<<j) <= n; i++) {
            st[i][j] = __gcd(st[i][j-1], st[i+(1<<(j-1))][j-1]); // change me
        }
    }
}

ll query(ll l, ll r) { // call me (result)
    l--, r--;
    ll k = logt[r-l+1];
    return __gcd(st[l][k], st[r-(1<<k)+1][k]); // change me
}
///////////////////// stop yanking /////////////////////

int main() {
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++) {
        cin >> arr[i];
    }
    build(n); // called
    ll q;
    cin >> q;
    while (q--) {
        ll l, r;
        cin >> l >> r;
        cout << query(l, r) << "\n"; // called
    }
    return 0;
}
