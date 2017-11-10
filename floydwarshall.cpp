#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// all pairs shortest path algorithm
// works only on non-negative edge weights
// both directed and undirected graphs
// Time complexity : O(V^3)

///////////////////// start yanking ////////////////////
const ll N = 1007;
ll graph[N][N], path[N][N];

void init(ll v) { // call me (precomputation)
    for (ll i = 1; i <= v; i++) {
        for (ll j = 1; j <= v; j++) {
            if (i == j) {
                graph[i][j] = 0, path[i][j] = i;
            } else {
                graph[i][j] = LLONG_MAX, path[i][j] = -1;
            }
        }
    }
}

void floydwarshall(ll v) { // call me (result)
    for (ll k = 1; k <= v; k++) {
        for (ll i = 1; i <= v; i++) {
            for (ll j = 1; j <= v; j++) {
                if (graph[i][k] != LLONG_MAX && graph[k][j] != LLONG_MAX && graph[i][k]+graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}

vector<ll> get_path(ll s, ll d) { // call me (result)
    vector<ll> p = {d};
    while (path[s][d] != s) {
        if (path[s][d] == -1) {
            return {};
        }
        p.push_back(path[s][d]);
        d = path[s][d];
    }
    p.push_back(s);
    reverse(p.begin(), p.end());
    return p;
}
///////////////////// stop yanking /////////////////////

int main() {
    ll v, e, s, d, w;
    cin >> v >> e;
    init(v);
    while (e--) {
        cin >> s >> d >> w;
        graph[s][d] = w;
        // graph[d][s] = w; // remove for directed
        path[s][d] = s;
    }
    floydwarshall(v); // called
    ll q;
    cin >> q;
    while (q--) {
        ll qt, s, d;
        cin >> qt >> s >> d;
        if (qt == 1) {
            if (graph[s][d] == LLONG_MAX) {
                cout << "inf";
            } else {
                cout << graph[s][d];
            }
        } else {
            auto p = get_path(s, d);
            for (auto &k : p) {
                cout << k << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}
