#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Kosaraju's algorithm
// TC: O(E+V), directed graph

///////////////////// start yanking ////////////////////
vector<vector<ll>> graph, grapht;
vector<bool> visited;
vector<ll> topo_sort, component;

void build(ll n) { // call me (precomputation)
    graph.resize(n+1), grapht.resize(n+1);
    visited.resize(n+1);
}

void insert_edge(ll s, ll d) { // call me (building)
    graph[s].push_back(d);
    grapht[d].push_back(s);
}

void dfs1(ll node) {
    visited[node] = true;
    for (auto &i : graph[node]) {
        if (!visited[i]) {
            dfs1(i);
        }
    }
    topo_sort.push_back(node);
}

void dfs2(ll node) {
    visited[node] = true;
    component.push_back(node);
    for (auto &i : grapht[node]) {
        if (!visited[i]) {
            dfs2(i);
        }
    }
}

vector<vector<ll>> strongly_connected_components() { // call me (result)
    vector<vector<ll>> scc;
    for (ll i = 1; i < graph.size(); i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }
    visited.assign(graph.size(), false);
    for (ll i = 1; i < graph.size(); i++) {
        ll node = topo_sort[grapht.size()-1-i];
        if (!visited[node]) {
            dfs2(node);
            scc.push_back(component);
            component.clear();
        }
    }
    return scc;
}
///////////////////// stop yanking /////////////////////

int main() {
    ll v, e, s, d;
    cin >> v;
    build(v); // called
    cin >> e;
    for (ll i = 0; i < e; i++) {
        cin >> s >> d;
        insert_edge(s, d); // called
    }
    auto scc = strongly_connected_components(); // called
    for (auto &vec : scc) {
        for (auto &node : vec) {
            cout << node << " ";
        }
        cout << "\n";
    }
    return 0;
}
