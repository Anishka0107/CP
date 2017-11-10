#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(E+V)
// BFS based, works only for unweighted graphs (or same weighted), finds minimum distance of all vertices considering all specific centers as sources
// If only single source, use just 1 specific center
// For weighted graphs with small weights, the egde can be split into multiple edges (introducing pseudo-vertices) each with gcd(all_weights) weight
// For weighted graphs with huge weights, simply use Dijkstra even if it is single source single destination (terminate those paths where distance reached is greater than already found distance between source and destination)
// For single source all/any destination in weighted DAG, use DFS
// For multiple source single destination in weighted graph, reverse graph and apply Dijkstra
// For multiple source all/any destination in weighted graph, initialize all sources set all sources to 0 distance and continue as normal
// For all/any source all/any destination, use Floyd Warshall or Johnson's algorithm

///////////////////// start yanking ////////////////////
vector<vector<ll>> graph;
vector<ll> specific_centers, distances;
queue<ll> q;

void build(ll n, ll k) { // call me (precomputation)
    graph.resize(n+1);
    distances.assign(n+1, LLONG_MAX);
    specific_centers.resize(k);
}

void insert_edge(ll s, ll d) {
    graph[s].push_back(d);
}

void bfs() { // call me (result)
    for (ll i = 0; i < specific_centers.size(); i++) {
        distances[specific_centers[i]] = 0;
        q.push(specific_centers[i]); 
    }
    while (!q.empty()) {
        ll curr = q.front();
        q.pop();
        for (auto &i : graph[curr]) {
            if (distances[i] > distances[curr]+1) {
                distances[i] = distances[curr]+1;
                q.push(i);
            }
        }
    }
}
///////////////////// stop yanking /////////////////////

int main() {
    ll v, e, k, s, d;
    cin >> v >> e >> k;
    build(v, k); // called
    for (ll i = 0; i < e; i++) {
        cin >> s >> d;
        insert_edge(s, d); // called
        insert_edge(d, s); // called
    }
    for (ll i = 0; i < k; i++) {
        cin >> specific_centers[i];
    }
    bfs(); // called
    for (ll i = 1; i < distances.size(); i++) {
        cout << distances[i] << " ";
    }
    return 0;
}
