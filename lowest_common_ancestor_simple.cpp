#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Lowest Common Ancestor in a DAG
// Sparse table based approach (called binary lifting), faster to code up and modify
// TC: O(n*log(n)) for precomputation, O(log(n)) per query

///////////////////// start yanking ////////////////////
ll n, l;
vector<ll> height;
vector<vector<ll>> graph, par;

void dfs(ll v, ll p) {
    par[v][0] = p;
    height[v] = height[p]+1;
    for (ll i = 1; i <= l; i++) {
        par[v][i] = par[par[v][i-1]][i-1];
    }
    for (auto &i : graph[v]) {
        if (p != i) {
            dfs(i, v);
        }
    }
}

void build_lca(ll root) { // call me (precomputation)
    l = ceil(log2(n));
    height.assign(n, -1);
    par.assign(n, vector<ll>(l+1));
    dfs(root, root);
}

ll lca(ll u, ll v) { // call me (result)
    if (height[u] < height[v]) {
        swap(u, v);
    }
    for (ll i = l; i >= 0; i--) {
        if (height[par[u][i]] >= height[v]) {
            u = par[u][i];
        }
    }
    if (u == v) {
        return u+1;
    }
    for (ll i = l; i >= 0; i--) {
        if (par[u][i] != par[v][i]) {
            u = par[u][i], v = par[v][i];
        }
    }
    return par[u][0]+1;
}

///////////////////// stop yanking /////////////////////

int main() {
    cin >> n;
    graph.resize(n);
    ll e, s, d;
    cin >> e;
    for (ll i = 0; i < e; i++) {
        cin >> s >> d; // s: parent, d: child
        graph[s-1].push_back(d-1);
    }
    build_lca(0); // called, assuming root's index as 0; if not, pass index of node with indegree 0
    ll q;
    cin >> q;
    while (q--) {
        ll u, v;
        cin >> u >> v;
        cout << lca(u-1, v-1) << "\n"; // called
    }
    return 0;
}
