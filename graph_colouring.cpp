#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(V*V)

///////////////////// start yanking ////////////////////
vector<vector<ll>> graph;
vector<ll> color;

void build(ll n) { // call me (precomputation)
    graph.resize(n+1);
    color.assign(n+1, -1);
}

void insert_edge(ll s, ll d) { // call me (building)
    graph[s].push_back(d);
}

void color_graph() { // call me (result)
    vector<bool> available(graph.size(), true);
    color[1] = 1;
    for (ll i = 2; i < graph.size(); i++) {
        for (ll j = 0; j < graph[i].size(); j++) {
            if (color[graph[i][j]] != -1) {
                available[color[graph[i][j]]] = false;
            }
        }
        for (ll j = 1; j < graph.size(); j++) {
            if (available[j]) {
                color[i] = j;
                break;
            }
        }
        for (ll j = 1; j < graph.size(); j++) {
            available[j] = true;
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
        insert_edge(d, s); // called
    }
    color_graph(); // called
    for (ll i = 1; i < color.size(); i++) {
        cout << color[i] << " ";
    }
    return 0;
}
