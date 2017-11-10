#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Lowest Common Ancestor in a DAG
// Few approaches to solve LCA (by reducing to RMQ) include sparse table, segment tree, square root decomposition, Tarjan's offline algorithm
// This is the most optimal (LCA reduced to RMQ on euler tour (utilises difference of 1 b/w consecutive elements) using sparse table), but quite difficult to code up in short time, and I never used it too
// TC: O(n) for precomputation, O(1) per query

///////////////////// start yanking ////////////////////
ll n, num_blocks, block_size;
vector<vector<vector<ll>>> rmq_blocks;
vector<vector<ll>> graph, st;
vector<ll> first_visit, euler_tour, height, logt, rmq_block_hash;

void dfs(ll v, ll h) {
    first_visit[v] = euler_tour.size();
    euler_tour.push_back(v);
    height[v] = h;
    for (auto &i : graph[v]) {
        if (height[i] == -1) {
            dfs(i, h+1);
            euler_tour.push_back(v);
        }
    }
}

void build_log() {
    logt.push_back(-1);
    for (ll i = 1; i <= euler_tour.size(); i++) {
        logt.push_back(logt[i/2]+1);
    }
}

ll minimum_height_index(ll i, ll j) {
    return height[euler_tour[i]] < height[euler_tour[j]] ? i : j;
}

void build_lca(ll root) { // call me (precomputation)
    first_visit.assign(n, -1);
    height.assign(n, -1);
    dfs(root, 0);
    build_log();
    block_size = max(ll(1), logt[euler_tour.size()]/2);
    num_blocks = (euler_tour.size()+block_size-1)/block_size;

    st.assign(num_blocks, vector<ll>(logt[num_blocks]+1));
    for (ll b = 0, i = 0, j = 0; i < euler_tour.size(); i++, j++) {
        if (j == block_size) {
            j = 0, ++b;
        }
        if (j == 0 || minimum_height_index(i, st[b][0]) == i) {
            st[b][0] = i;
        }
    }
    for (ll j = 1; j <= logt[num_blocks]; j++) {
        for (ll i = 0; i < num_blocks; i++) {
            ll ni = i+(1<<(j-1));
            if (ni >= num_blocks) {
                st[i][j] = st[i][j-1];
            } else {
                st[i][j] = minimum_height_index(st[i][j-1], st[ni][j-1]);
            }
        }
    }

    rmq_block_hash.assign(num_blocks, 0);
    for (ll b = 0, i = 0, j = 0; i < euler_tour.size(); i++, j++) {
        if (j == block_size) {
            j = 0, ++b;
        }
        if (j > 0 && (i >= euler_tour.size() || minimum_height_index(i-1, i) == i-1)) {
            rmq_block_hash[b] += 1<<(j-1);
        }
    }

    rmq_blocks.resize(1<<(block_size-1));
    for (ll i = 0; i < num_blocks; i++) {
        ll hash = rmq_block_hash[i];
        if (!rmq_blocks[hash].empty()) {
            continue;
        }
        rmq_blocks[hash].assign(block_size, vector<ll>(block_size));
        for (ll l = 0; l < block_size; l++) {
            rmq_blocks[hash][l][l] = l;
            for (ll r = l+1; r < block_size; r++) {
                rmq_blocks[hash][l][r] = rmq_blocks[hash][l][r-1];
                if (i*block_size+r < euler_tour.size()) {
                    rmq_blocks[hash][l][r] = minimum_height_index(i*block_size+rmq_blocks[hash][l][r], i*block_size+r) - i*block_size;
                }
            }
        }
    }
}

ll lca_in_block(ll b, ll l, ll r) {
    return rmq_blocks[rmq_block_hash[b]][l][r] + b*block_size;
}

ll lca(ll u, ll v) { // call me (result)
    ll l = first_visit[u], r = first_visit[v];
    if (l > r) {
        swap(l, r);
    }
    ll bl = l/block_size, br = r/block_size;
    if (bl == br) {
        return euler_tour[lca_in_block(bl, l%block_size, r%block_size)]+1;
    }
    ll ans1 = lca_in_block(bl, l%block_size, block_size-1), ans2 = lca_in_block(br, 0, r%block_size);
    ll ans = minimum_height_index(ans1, ans2);
    if (bl+1 < br) {
        ll pw = logt[br-bl-1];
        ll ans3 = st[bl+1][pw], ans4 = st[br-(1<<pw)][pw];
        ans = minimum_height_index(ans, minimum_height_index(ans3, ans4));
    }
    return euler_tour[ans]+1;
}
///////////////////// stop yanking /////////////////////

int main() {
    cin >> n;
    graph.resize(n);
    ll e, s, d;
    cin >> e;
    for (ll i = 0; i < e; i++) {
        cin >> s >> d; // s: parent, d: child
        graph[s-1].push_back(d-1);
    }
    build_lca(0); // called, assuming root's index as 0; if not, pass index of node with indegree 0
    ll q;
    cin >> q;
    while (q--) {
        ll u, v;
        cin >> u >> v;
        cout << lca(u-1, v-1) << "\n"; // called
    }
    return 0;
}
