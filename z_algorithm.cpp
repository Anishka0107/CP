#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Searches for all occurrences of pattern in string
// TC: O(n) -> O(s+p) 

///////////////////// start yanking ////////////////////
vector<ll> z_function(string s) {
    vector<ll> z(s.size());
    for (ll i = 1, l = 0, r = 0; i < s.size(); i++) {
        if (i <= r) {
            z[i] = min(r-i+1, z[i-l]);
        }
        while (i+z[i] < s.size() && s[z[i]] == s[i+z[i]]) {
            z[i]++;
        }
        if (i+z[i]-1 > r) {
            l = i, r = i+z[i]-1;
        }
    }
    return z;
}

vector<ll> z_search(const string &str, const string &pat) {
    string sep = "%"; // separator must NOT be present in string or pattern
    string concat = pat + sep + str;
    vector<ll> z = z_function(concat), indices;
    for (ll i = 0; i < str.size(); i++) {
        if (z[i+pat.size()+1] == pat.size()) {
            indices.push_back(i);
        }
    }
    return indices;
}

///////////////////// stop yanking /////////////////////

int main() {
    string str, pat;
    getline(cin, str); 
    getline(cin, pat);
    auto indices = z_search(str, pat); // called
    for (auto &index : indices) {
        cout << index << " ";
    }
    return 0;
}
