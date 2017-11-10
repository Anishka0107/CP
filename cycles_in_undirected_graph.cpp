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

bool __dfs(ll start, ll par) {
    visited[start] = true;
    for (ll i = 0; i < graph[start].size(); i++) {
        if (!visited[graph[start][i]]) {
            if (__dfs(graph[start][i], start)) {
                return true;
            }
        } else if (graph[start][i] != par) {
            return true;
        }
    }
    return false;
}

bool is_cyclic() { // call me (result)
    for (ll i = 1; i < graph.size(); i++) {
        if (!visited[i] && __dfs(i, -1)){
            return true;
        }
    }
    return false;
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
        insert_edge(d, s); // called
    }
    if (is_cyclic()) { // called
        cout << "yes";
    } else {
        cout << "no";
    }
    return 0;
}
