#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(E*log(E*V))

///////////////////// start yanking ////////////////////
struct edge {
    ll s, d, w;
};
vector<edge> edges;
vector<ll> ds, sizes;

bool scomp(const edge& a, const edge& b) {
    return a.w < b.w;
}

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

void union_set(ll a, ll b) {
    ll ra = get_root(a), rb = get_root(b);
    if (sizes[ra] > sizes[rb]) {
        ds[rb] = ds[ra];
        sizes[ra] += sizes[rb];
    } else {
        ds[ra] = ds[rb];
        sizes[rb] += sizes[ra];
    }
}

ll kruskal(ll v, vector<edge> &mst) { // call me (result)
    make_set(v);
    sort(edges.begin(), edges.end(), scomp);
    ll min_cost = 0;
    for (ll i = 0; i < edges.size(); i++) {
        if (get_root(edges[i].s) != get_root(edges[i].d)) {
            min_cost += edges[i].w;
            mst.push_back(edges[i]);
            union_set(edges[i].s, edges[i].d);
        }
    }
    return min_cost;
}
///////////////////// stop yanking /////////////////////

int main() {
    ll v, e, s, d, w;
    cin >> v >> e;
    for (ll i = 0; i < e; i++) {
        cin >> s >> d >> w;
        edges.push_back({s, d, w}); // called, undirected
    }
    vector<edge> mst;
    cout << kruskal(v, mst) << "\n"; // called
    for (auto &i : mst) {
        cout << i.s << " -> " << i.d << " : " << i.w << "\n";
    }
    return 0;
}
