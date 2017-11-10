#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(n*(log(n))^2) for SA precomputation, O(n) for LCP precomputation; O(log(n)) or O(single RMQ) for LCP (longest common prefix) query; SC: O(n*log(n))

///////////////////// start yanking ////////////////////
const int FIRST_CHAR = (int)'a';
const ll N = 1000000, K = ceil(log2(N));
ll P[K][N], pow2[K], step, n; // P[i][j] stores rank of j-th suffix after suffixes have been sorted by their first 2^i characters
vector<ll> sa, lcp; // lcp[i] stores lcp of sa[i] and sa[i+1]

struct rank_ {
    ll first, second, index;
    bool operator < (rank_ r) {
        if (first != r.first) {
            return first < r.first;
        }
        return second < r.second;
    }
};

void build_suffix_array(const string &s) { // call me (precomputation)
    n = s.size();
    sa.resize(n);
    vector<rank_> ranks(n);
    pow2[0] = 1;
    for (ll i = 1; i < ceil(log2(n)); i++) {
        pow2[i] = 2*pow2[i-1];
    }
    for (ll i = 0; i < n; i++) {
        P[0][i] = s[i] - FIRST_CHAR;
    }
    step = 1;
    for (ll i = 1; pow2[i-1] < n; i++, step++) {
        for (ll j = 0; j < n; j++) {
            ranks[j] = {P[i-1][j], (j+pow2[i-1] < n) ? P[i-1][j+pow2[i-1]] : -1, j};
        }
        sort(ranks.begin(), ranks.end());
        for (ll j = 0; j < n; j++) {
            P[i][ranks[j].index] = (j > 0 && ranks[j].first == ranks[j-1].first && ranks[j].second == ranks[j-1].second) ? P[i][ranks[j-1].index] : j;
        }
    }
    step--;
    for (ll i = 0; i < n; i++) {
        sa[P[step][i]] = i;
    }
}

void build_lcp(const string &s) { // call me (precomputation)
    vector<ll> ranks(n);
    for (ll i = 0; i < n; i++) {
        ranks[sa[i]] = i;
    }
    ll k = 0;
    lcp.resize(n-1);
    for (ll i = 0; i < n; i++) {
        if (ranks[i] == n-1) {
            k = 0;
            continue;
        }
        ll j = sa[ranks[i]+1];
        while (i+k < n && j+k < n && s[i+k] == s[j+k]) {
            k++;
        }
        lcp[ranks[i]] = k;
        if (k) {
            k--;
        }
    }
}

ll query_built_lcp() { // For multiple queries using LCP array, O(1) or O(log(n)) or O(sqrt(n))
    // Copy any RMQ code (sparse table for O(1) or segtree for O(log(n)) or anything else)
}

ll get_lcp(ll i, ll j) { // TC: O(log(n)) single query without using prebuilt LCP array
    if (i == j) {
        return n-i+1;
    }
    ll ans = 0;
    for (ll k = step; k >= 0; k--) {
        if (P[k][i] == P[k][j]) {
            ans += pow2[k], i += pow2[k], j += pow2[k];
        }
    }
    return ans;
}
///////////////////// stop yanking /////////////////////

int main() {
    string s;
    cin >> s;
    build_suffix_array(s); // called
    for (ll i = 0; i < s.size(); i++) {
        cout << sa[i] << " ";
    }
    cout << "\n";
    ll i, j;
    cin >> i >> j; // 0-indexed
    cout << get_lcp(i, j) << "\n"; // called
    build_lcp(s); // called
    for (ll i = 0; i < s.size()-1; i++) {
        cout << lcp[i] << " ";
    }
    /*
    cout << "\n";
    ll q;
    cin >> q;
    while (q--) {
        cin >> i >> j;
        cout << query_built_lcp(i, j); // called
    }
    */
    return 0;
}
