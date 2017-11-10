#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(E+V)

///////////////////// start yanking ////////////////////
vector<vector<ll>> graph;
vector<int> color;

void build(ll n) { // call me (precomputation)
    graph.resize(n+1);
    color.assign(n+1, -1);
}

void insert_edge(ll s, ll d) { // call me (building)
    graph[s].push_back(d);
}

bool is_bipartite(ll start, int c) {
    if (color[start] == c) {
        return true;
    }
    if (color[start] != -1) {
        return false;
    }
    color[start] = c;
    for (ll i = 0; i < graph[start].size(); i++) {
        if (!is_bipartite(graph[start][i], 1-c)) {
            return false;
        }
    }
    return true;
}

bool is_bipartite() { // call me (result)
    for (ll i = 1; i < graph.size(); i++) {
        if (color[i] == -1 && !is_bipartite(i, 1)) {
            return false;
        }
    }
    return true;
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
        insert_edge(d, s); // called, remove if graph is undirected
    }
    if (is_bipartite()) { // called
        cout << "yes";
    } else {
        cout << "no";
    }
    return 0;
}
