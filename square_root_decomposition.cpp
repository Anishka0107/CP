#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Range minimum query with updates
// TC: O(n) for precomputation, O(sqrt(n)) per query (any type), SC: O(n)
// TODO: optimize by replacing division operator

///////////////////// start yanking ////////////////////
const ll N = 1000007, SQN = sqrt(N);
ll arr[N], blocks[SQN] = {LONG_LONG_MAX}, lazy[SQN];

void build(ll n) { // call me (precomputation)
    ll sq = sqrt(n), num_blocks = ceil(double(n)/sq);
    for (ll i = 0; i < num_blocks; i++) {
        blocks[i] = LONG_LONG_MAX;
        for (ll j = i*sq; j < n && j < (i+1)*sq; j++) {
            blocks[i] = min(blocks[i], arr[j]);
        }
    }
}

ll query_range(const ll l, const ll r, const ll n) { // call me (result)
    ll rmq = LONG_LONG_MAX, sq = sqrt(n), i = l;
    for (i = l; i%sq && i <= r; i++) {
        rmq = min(rmq, arr[i] + lazy[l/sq]);
    }
    for (; i+sq <= r; i += sq) {
        rmq = min(rmq, blocks[i/sq]);
    }
    for (; i <= r; i++) {
        rmq = min(rmq, arr[i] + lazy[r/sq]);
    }
    return rmq;
}

void update_range(const ll l, const ll r, const ll k, const ll n) { // increment by value, call me (result)
    ll sq = sqrt(n), i = l;
    if (l%sq != 0) {
        for (i = l; i%sq && i <= r; i++) {
            arr[i] += k;
        }
        blocks[l/sq] = LONG_LONG_MAX;
        for (i = (l/sq)*sq; i < ((l/sq)+1)*sq && i < n; i++) {
            arr[i] += lazy[l/sq]; // to set, change += to =
            blocks[l/sq] = min(blocks[l/sq], arr[i]);
        }
        lazy[l/sq] = 0;
    }
    for (; i+sq <= r; i += sq) {
        lazy[i/sq] += k;
        blocks[i/sq] += k;
    }
    if (i <= r) {
        for (; i <= r; i++) {
            arr[i] += k;
        }
        blocks[r/sq] = LONG_LONG_MAX;
        for (i = (r/sq)*sq; i < ((r/sq)+1)*sq && i < n; i++) {
            arr[i] += lazy[r/sq]; // to set, change += to =
            blocks[r/sq] = min(blocks[r/sq], arr[i]);
        }
        lazy[r/sq] = 0;
    }
}
///////////////////// stop yanking /////////////////////

int main() {
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++) {
        cin >> arr[i];
    }
    build(n); // called
    cout << endl;
    ll q;
    cin >> q;
    while (q--) {
        ll ch, left, right;
        cin >> ch >> left >> right;
        if (ch == 1) {
            cout << query_range(left-1, right-1, n) << "\n"; // called
        } else {
            ll k;
            cin >> k;
            update_range(left-1, right-1, k, n); // called
        }
    }
    return 0;
}
