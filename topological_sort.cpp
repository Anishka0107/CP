#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// For directed acyclic graphs only
// It has atleast 1 vertex with indegree 0 and 1 with outdegree 0
// TC: O(E+V)

///////////////////// start yanking ////////////////////
vector<vector<ll>> graph;
vector<bool> visited;

void build(ll n) { // call me (precomputation)
    graph.resize(n+1);
    visited.resize(n+1);
}

void insert_edge(ll s, ll d) { // call me (building)
    graph[s].push_back(d);
}

void dfs(stack<ll> &s, ll v) {
    visited[v] = true;
    for (auto &i : graph[v]) {
        if (!visited[i]) {
            dfs(s, i);
        }
    }
    s.push(v);
}

void topo_sort() { // call me (result)
    stack<ll> s;
    for (ll i = 1; i < graph.size(); i++) {
        if (!visited[i]) {
            dfs(s, i);
        }
    }
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
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
    }
    topo_sort(); // called
    return 0;
}
