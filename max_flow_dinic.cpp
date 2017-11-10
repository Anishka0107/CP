#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(E*V^2)

///////////////////// start yanking ////////////////////
struct edge {
    ll d; // destination
    ll f; // flow
    ll c; // capacity
    ll r_idx; // index of reverse edge in graph
};

vector<vector<edge>> graph;
vector<ll> level, ptr;

void build(ll n) { // call me (initialization)
    graph.resize(n+1);
    level.resize(n+1);
    ptr.resize(n+1);
}

void insert_edge(ll s, ll d, ll c) { // call me (building)
    graph[s].push_back({d, 0, c, (ll)graph[d].size()});
    graph[d].push_back({s, 0, 0, (ll)graph[s].size() - 1});
}

ll dfs(ll s, ll d, ll flow) {
    if (s == d || !flow) {
        return flow;
    }
    for (; ptr[s] < graph[s].size(); ptr[s]++) {
        edge &e = graph[s][ptr[s]];
        if (level[e.d] == level[s] + 1 && e.f < e.c) {
            if (ll curr_flow = dfs(e.d, d, min(flow, e.c - e.f)) > 0) {
                e.f += curr_flow;
                graph[e.d][e.r_idx].f -= curr_flow;
                return curr_flow;
            }
        }
    }
    return 0;
}

bool bfs(ll s, ll d) {
    fill(level.begin(), level.end(), LONG_LONG_MAX);
    level[s] = 0;
    queue<ll> q;
    q.push(s);
    while (!q.empty()) {
        ll v = q.front();
        q.pop();
        for (auto &e : graph[v]) {
            if (level[e.d] == LONG_LONG_MAX && e.f < e.c) {
                level[e.d] = level[v] + 1;
                q.push(e.d);
            }
        }
    }
    return level[d] != LONG_LONG_MAX;
}

ll max_flow_dinic(ll source, ll sink) { // call me (result)
    ll max_flow = 0;
    while (bfs(source, sink)) {
        fill(ptr.begin(), ptr.end(), 0);
        while (ll curr_flow = dfs(source, sink, LONG_LONG_MAX)) {
            max_flow += curr_flow;
        }
    }
    return max_flow;
}
///////////////////// stop yanking /////////////////////

signed main() {
    ll v, e, s, d, c;
    cin >> v;
    build(v); // called
    cin >> e;
    for (ll i = 0; i < e; i++) {
        cin >> s >> d >> c;
        insert_edge(s, d, c); // called
    }
    cin >> s >> d;
    cout << max_flow_dinic(s, d) << "\n"; // called
    return 0;
}
