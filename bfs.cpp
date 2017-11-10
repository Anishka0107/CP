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

void __bfs(ll start) { // call me (result), BFS from source
    queue<ll> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        start = q.front();
        q.pop();
        cout << start << " ";
        for (ll i = 0; i < graph[start].size(); i++) {
            if (!visited[graph[start][i]]) {
                visited[graph[start][i]] = true;
                q.push(graph[start][i]);
            }
        }
    }
}

void bfs() { // call me (result), complete BFS
    for (int i = 1; i < graph.size(); i++) {
        if (!visited[i]) {
            __bfs(i);
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
    bfs(); // called
    cout << "\n";
    cin >> s;
    __bfs(s); // called
    return 0;
}
