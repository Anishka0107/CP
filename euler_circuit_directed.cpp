#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Hierholzer's algorithm
// TC: O(E+V)

///////////////////// start yanking ////////////////////
vector<vector<ll>> graph, grapht;
vector<ll> degree, indegree, outdegree;
vector<bool> visited;
vector<ll> topo_sort;
ll cnt;

void build(ll n) { // call me (precomputation)
    graph.resize(n+1), grapht.resize(n+1);
    degree.resize(n+1), indegree.resize(n+1), outdegree.resize(n+1);
    visited.resize(n+1);
}

void insert_edge(ll s, ll d) { // call me (building)
    graph[s].push_back(d);
    grapht[d].push_back(s);
    degree[s]++, outdegree[s]++, indegree[d]++;
}

void dfs1(ll node) {
    visited[node] = true;
    for (auto &i : graph[node]) {
        if (!visited[i]) {
            dfs1(i);
        }
    }
    topo_sort.push_back(node);
}

void dfs2(ll node) {
    visited[node] = true;
    cnt++;
    for (auto &i : grapht[node]) {
        if (!visited[i]) {
            dfs2(i);
        }
    }
}

// All vertices have indegree = outdegree and all nonzero degree vertices are in same strongly connected component
bool check_if_euler() { // call me (result)
    ll node = -1, num_nodes = 0;
    for (ll i = 1; i < graph.size(); i++) {
        if (indegree[i] != outdegree[i]) {
            return false;
        }
        if (degree[i] > 0) {
            node = i;
            num_nodes++;
        }
    }
    if (node == -1) {
        return true;
    }
    dfs1(node);
    visited.assign(graph.size(), false);
    dfs2(topo_sort[topo_sort.size()-1]);
    return num_nodes == cnt;
}

vector<ll> euler_circuit() { // call me (result)
    ll node = 1; // starting point of euler circuit, change if needed
    vector<ll> circuit;
    stack<ll> st;
    st.push(node);
    while (!st.empty()) {
        if (degree[node]) {
            st.push(node);
            degree[node]--;
            node = graph[node].back();
            graph[st.top()].pop_back();
        } else {
            circuit.push_back(node);
            node = st.top();
            st.pop();
        }
    }
    reverse(circuit.begin(), circuit.end());
    return circuit;
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
    if (!check_if_euler()) { // called
        cout << "no";
        return 0;
    }
    auto ec = euler_circuit(); // called
    for (auto &node : ec) {
        cout << node << " ";
    }
    return 0;
}
