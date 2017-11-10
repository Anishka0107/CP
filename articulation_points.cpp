#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(E+V)

///////////////////// start yanking ////////////////////
vector<vector<ll>> graph;
vector<bool> visited, ap;
vector<ll> disc, low;
ll timer;

void build(ll n) { // call me (precomputation)
    graph.resize(n+1);
    visited.resize(n+1), ap.resize(n+1);
    disc.resize(n+1), low.resize(n+1);
}

void insert_edge(ll s, ll d) { // call me (building)
    graph[s].push_back(d);
    graph[d].push_back(s); // remove if directed
}

void dfs(ll start, ll p = -1) {
    visited[start] = true, disc[start] = low[start] = ++timer;
    ll num_child = 0;
    for (auto &i : graph[start]) {
        if (!visited[i]) {
            dfs(i, start);
            low[start] = min(low[start], low[i]);
            num_child++;
            if ((p == -1 && num_child > 1) || (p != -1 && low[i] >= disc[start])) {
                ap[start] = true;
            }
        } else if (i != p) {
            low[start] = min(low[start], disc[i]);
        }
    }
}

void find_ap() { // call me (result)
    for (ll i = 1; i < graph.size(); i++) {
        if (!visited[i]) {
            dfs(i);
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
    }
    find_ap(); // called
    for (ll i = 1; i < ap.size(); i++) {
        if (ap[i]) {
            cout << i << " ";
        }
    }
    return 0;
}
