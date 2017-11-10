#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Hierholzer's algorithm
// TC: O(E+V)

///////////////////// start yanking ////////////////////
vector<vector<pair<ll, ll>>> graph; // first stores the vertex, second stores the index it is inserted at in the vector of the other vertex
vector<ll> degree;
vector<bool> visited;
ll cnt;

void build(ll n) { // call me (precomputation)
    graph.resize(n+1);
    degree.resize(n+1);
    visited.resize(n+1);
}

void insert_edge(ll s, ll d) { // call me (building)
    graph[s].push_back({d, graph[d].size()});
    graph[d].push_back({s, graph[s].size()-1});
    degree[s]++;
    degree[d]++;
}

void dfs(ll s) {
    visited[s] = true;
    cnt++;
    for (auto &i : graph[s]) {
        if (!visited[i.first]) {
            dfs(i.first);
        }
    }
}

// undirected: all even degree vertices and all non-zero degree vertices are in same connected component
bool check_if_euler() { // call me (result)
    ll node = -1, num_nodes = 0;
    for (ll i = 1; i < graph.size(); i++) {
        if (degree[i] & 1) {
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
    dfs(node);
    return cnt == num_nodes;
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
            while (graph[node].back().second == -1) {
                graph[node].pop_back();
            }
            ll newidx = graph[node].back().second;
            node = graph[node].back().first;
            degree[node]--;
            graph[node][newidx].second = -1;
            graph[st.top()].pop_back();
        } else {
            circuit.push_back(node);
            node = st.top();
            st.pop();
        }
    }
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
