#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Queries the number of distinct elements in a segment
// Works only for offline queries without any updates; brother of square root decomposition
// TC: O(q*log(q)) for precomputation, O((q+n)*sqrt(n)) for all queries

///////////////////// start yanking ////////////////////
const ll N = 100007, Q = 1000007, SQQ = sqrt(Q), MAXELE = 1000011;
ll arr[N], ct[MAXELE], result[Q], res;

struct _q {
    ll l, r, i;
} query[Q];

bool qcomp(_q &a, _q &b) {
	if (a.l/SQQ != b.l/SQQ) {
		return a.l/SQQ < b.l/SQQ;
	}
	return a.r < b.r;
}

void add(ll pos, ll i) { // change me
    ct[arr[pos]]++;
    if (ct[arr[pos]] == 1) {
        res++;
    }
}

void remove(ll pos, ll i) { // change me
    ct[arr[pos]]--;
    if (ct[arr[pos]] == 0) {
        res--;
    }
}

void mo(ll n, ll q) { // call me (result)
    sort(query, query + q, qcomp);
    ll cl = 0, cr = 0;
    for (ll i = 0; i < q; i++) {
        while (cl < query[i].l) {
            remove(cl, i);
            cl++;
        }
        while (cl > query[i].l) {
            add(cl-1, i);
            cl--;
        }
        while (cr < query[i].r+1) {
            add(cr, i);
            cr++;
        }
        while (cr > query[i].r+1) {
            remove(cr-1, i);
            cr--;
        }
        result[query[i].i] = res;
    }
}
///////////////////// stop yanking /////////////////////

int main() {
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++) {
        cin >> arr[i];
    }
    ll q;
    cin >> q;
    for (ll i = 0; i < q; i++) {
        cin >> query[i].l >> query[i].r;
        query[i].i = i, query[i].l--, query[i].r--;
    }
    mo(n, q); // called
    for (ll i = 0; i < q; i++) {
        cout << result[i] << "\n";
    }
    return 0;
}
