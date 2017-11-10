#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(E+V), undirected graph

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

void __dfs(ll start, vector<ll> &cdfs) {
    visited[start] = true;
    cdfs.push_back(start);
    for (ll i = 0; i < graph[start].size(); i++) {
        if (!visited[graph[start][i]]) {
            __dfs(graph[start][i], cdfs);
        }
    }
}

vector<vector<ll>> connected_components() { // call me (result)
    vector<vector<ll>> cc;
    vector<ll> cdfs;
    for (ll i = 1; i < graph.size(); i++) {
        if (!visited[i]) {
            __dfs(i, cdfs);
            cc.push_back(cdfs);
            cdfs.clear();
        }
    }
    return cc;
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
    auto cc = connected_components(); // called
    for (auto &_cc : cc) {
        for (auto &c : _cc) {
            cout << c << " ";
        }
        cout << "\n";
    }
    return 0;
}
