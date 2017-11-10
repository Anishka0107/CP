#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

///////////////////// start yanking ////////////////////
vector<ll> ds, sizes;

void make_set(ll n) { // call me (precomputation)
    ds.resize(n+1);
    sizes.resize(n+1);
    for (int i = 1; i <= n; i++) {
        ds[i] = i;
        sizes[i] = 1;
    }
}

ll get_root(ll i) {
    while (ds[i] != i) {
        ds[i] = ds[ds[i]];
        i = ds[i];
    }
    return i;
}

void union_set(ll a, ll b) { // call me (result), TC: O(log*n)
    ll ra = get_root(a), rb = get_root(b);
    if (sizes[ra] > sizes[rb]) {
        ds[rb] = ds[ra];
        sizes[ra] += sizes[rb];
    } else {
        ds[ra] = ds[rb];
        sizes[rb] += sizes[ra];
    }
}

bool find_set(ll a, ll b) { // call me (result), TC: O(log*n)
    return get_root(a) == get_root(b);
}
///////////////////// stop yanking /////////////////////

int main() {
    ll n;
    cin >> n;
    make_set(n);
    ll q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        short p;
        ll a, b;
        cin >> p >> a >> b;
        if (p == 1) {
            union_set(a, b);
        } else {
            cout << find_set(a, b) << "\n";
        }
    }
    return 0;
}
