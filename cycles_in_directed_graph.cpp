#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(E+V)

///////////////////// start yanking ////////////////////
vector<vector<ll>> graph;
vector<bool> visited, curr_dfs;

void build(ll n) { // call me (initialization)
    graph.resize(n+1);
    visited.resize(n+1);
    curr_dfs.resize(n+1);
}

void insert_edge(ll s, ll d) { // call me (building)
    graph[s].push_back(d);
}

bool __dfs(ll start) {
    visited[start] = true;
    curr_dfs[start] = true;
    for (ll i = 0; i < graph[start].size(); i++) {
        if (!visited[graph[start][i]] && __dfs(graph[start][i])) {
            return true;
        } else if (curr_dfs[graph[start][i]]) {
            return true;
        }
    }
    curr_dfs[start] = false;
    return false;
}

bool is_cyclic() { // call me (result)
    for (ll i = 1; i < graph.size(); i++) {
        if (!visited[i] && __dfs(i)){
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
    }
    if (is_cyclic()) { // called
        cout << "yes";
    } else {
        cout << "no";
    }
    return 0;
}
