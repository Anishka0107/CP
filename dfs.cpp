#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(E+V)

///////////////////// start yanking ////////////////////
vector<vector<ll>> graph;
vector<bool> visited;

void build(ll n) { // call me (initialization)
    graph.resize(n+1);
    visited.resize(n+1);
}

void insert_edge(ll s, ll d) { // call me (building)
    graph[s].push_back(d);
}

void __dfs(ll start) { // call me (result), DFS from source
    visited[start] = true;
    cout << start << " ";
    for (ll i = 0; i < graph[start].size(); i++) {
        if (!visited[graph[start][i]]) {
            __dfs(graph[start][i]);
        }
    }
}

void dfs() { // call me (result), complete DFS
    for (ll i = 1; i < graph.size(); i++) {
        if (!visited[i]) {
            __dfs(i);
        }
    }
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
    dfs(); // called
    cout << "\n";
    cin >> s;
    __dfs(s); // called
    return 0;
}
