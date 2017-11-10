#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// single source shortest path algorithm
// works on negative edge weights as well
// both directed and undirected graphs
// Time complexity : O(V*E)

///////////////////// start yanking ////////////////////
struct edge {
    ll s, d, w;
};
vector<edge> edges;
vector<ll> dist; // stores the answer

void bellman_ford(ll s, ll v) {
    dist[s] = 0;
    for (ll i = 1; i < v; i++) {
        for (ll j = 0; j < edges.size(); j++) {
            if (dist[edges[j].s] != LLONG_MAX && dist[edges[j].s] + edges[j].w < dist[edges[j].d]) {
                dist[edges[j].d] = dist[edges[j].s] + edges[j].w;
            }
        }
    }
    for (ll i = 0; i < edges.size(); i++) {
        assert(dist[edges[i].s] == LLONG_MAX || dist[edges[i].s] + edges[i].w >= dist[edges[i].d]); // negative weight cycle exists
    }
}
///////////////////// stop yanking /////////////////////

int main() {
    ll v, e, s, d, w;
    cin >> v >> e;
    dist.assign(v+1, LLONG_MAX);
    while (e--) {
        cin >> s >> d >> w;
        edges.push_back({s, d, w});
    }
    cin >> s;
    bellman_ford(s, v); // called
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
