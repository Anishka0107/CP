#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// single source shortest path algorithm
// can be extended for multi-source (being considered simultaneously); but not all sources (separate) shortest path (use Floyd Warshall or Johnson instead)
// works only on non-negative edge weights
// both directed and undirected graphs
// Time complexity : O(E+V*logV)

///////////////////// start yanking ////////////////////
struct _priority {
    bool operator() (const pair<ll, ll> &a, const pair<ll, ll> &b) const {
        return a.second > b.second;  // comparison in min heap based on distance
    }
};

vector<vector<pair<ll, ll>>> graph;  // first denotes the destination vertex, second denotes the weight/distance
vector<ll> dist; // stores the answer
priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, _priority> pq;

void dijkstra(ll s) {
    dist[s] = 0;
    pq.push(make_pair(s, 0));
    while (!pq.empty()) {
        auto v = pq.top();
        pq.pop();
        for (ll i = 0; i < graph[v.first].size(); i++) {
            auto node = graph[v.first][i];
            if (dist[node.first] > dist[v.first] + node.second) {
                dist[node.first] = dist[v.first] + node.second;
                pq.push(make_pair(node.first, dist[node.first]));
            }
        }
    }
}
///////////////////// stop yanking /////////////////////

int main() {
    ll v, e, s, d, w;
    cin >> v >> e;
    graph.resize(v+1);
    dist.assign(v+1, LLONG_MAX);
    while (e--) {
        cin >> s >> d >> w; // undirected
        graph[s].push_back(make_pair(d, w));
        graph[d].push_back(make_pair(s, w));
    }
    cin >> s;
    dijkstra(s); // called
    for (ll i = 1; i <= v; i++) {
        if (dist[i] == LLONG_MAX) {
            cout << "inf";
        } else {
            cout << dist[i];
        }
        cout << " ";
    }
    return 0;
}
