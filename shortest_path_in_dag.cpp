#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(E+V)

///////////////////// start yanking ////////////////////
vector<vector<pair<ll, ll>>> graph; // first: destination, second: weight
vector<bool> visited;

void build(ll n) { // call me (precomputation)
    graph.resize(n+1);
    visited.resize(n+1);
}

void insert_edge(ll s, ll d, ll w) { // call me (building)
    graph[s].push_back({d, w});
}

void dfs(stack<ll> &st, ll v) {
    visited[v] = true;
    for (auto &i : graph[v]) {
        if (!visited[i.first]) {
            dfs(st, i.first);
        }
    }
    st.push(v);
}

stack<ll> topo_sort() { // call me (result)
    stack<ll> st;
    for (ll i = 1; i < graph.size(); i++) {
        if (!visited[i]) {
            dfs(st, i);
        }
    }
    return st;
}

vector<ll> shortest_path(ll s) {
    stack<ll> st = topo_sort();
    vector<ll> distance(graph.size(), LLONG_MAX);
    distance[s] = 0;
    while (!st.empty()) {
        ll v = st.top();
        st.pop();
        if (distance[v] != LLONG_MAX) {
            for (auto &i : graph[v]) {
                if (distance[i.first] > distance[v] + i.second) {
                    distance[i.first] = distance[v] + i.second;
                }
            }
        }
    }
    return distance;
}
///////////////////// stop yanking /////////////////////

int main() {
    ll v, e, s, d, w;
    cin >> v >> e;
    build(v); // called
    for (ll i = 0; i < e; i++) {
        cin >> s >> d >> w;
        insert_edge(s, d, w); // called
    }
    cin >> s;
    auto sp = shortest_path(s); // called
    for (ll i = 1; i < sp.size();i++) {
        if (sp[i] != LLONG_MAX) {
            cout << sp[i];
        } else {
            cout << "inf";
        }
        cout << " ";
    }
    return 0;
}
