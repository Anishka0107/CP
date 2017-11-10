#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(log(n))
// The below code if for n'th fibonacci number
// | f(n)   | = Z^(n-2) X | f(2) | where Z = | 1 1 |
// | f(n-1) |             | f(1) |           | 1 0 |
// which is f(n) = 1*f(n-1) + 1*f(n-2); f(1) = 0, f(2) = 1
// Z^(n-2) can be found out by exponentiation (include modulus if required)
// Other problems can be solved similarly after calculating their Z matrix
// Eg: | f(n)   |  = | a b c | X | f(n-1) | for f(n) = a*f(n-1) + b*f(n-2) + c*f(n-3)
//     | f(n-1) |    | 1 0 0 |   | f(n-2) |
//     | f(n-2) |    | 0 1 0 |   | f(n-3) |
// Eg: | f(n+1) | = | 1 1 1 | X | f(n)   | for f(n) = f(n-1) + f(n-2) + c 
//     | f(n)   |   | 1 0 0 |   | f(n-1) |
//     | c      |   | 0 0 1 |   | c      |

///////////////////// start yanking ////////////////////
void mat_mul(vector<vector<ll>> &a, vector<vector<ll>> &b, vector<vector<ll>> &res, ll mod) {
    for (ll i = 0; i < a.size(); i++) {
        for (ll j = 0; j < a.size(); j++) {
            res[i][j] = 0;
            for (ll k = 0; k < a.size(); k++) {
                res[i][j] += (a[i][k] * b[k][j]) % mod;
            }
        }
    }
}

vector<vector<ll>> mat_pow(vector<vector<ll>> Z, ll n, ll mod) {
    vector<vector<ll>> ans(Z.size(), vector<ll>(Z.size())), temp(Z.size(), vector<ll>(Z.size()));
    for (ll i = 0; i < Z.size(); i++) { // identity matrix of size n
        for (ll j = 0; j < Z.size(); j++) {
            if (i == j) {
                ans[i][j] = 1;
            }
        }
    }
    while (n > 0) {
        if (n & 1) {
            mat_mul(ans, Z, temp, mod);
            ans = temp;
        }
        n >>= 1;
        mat_mul(Z, Z, temp, mod);
        Z = temp;
    }
    return ans;
}

ll fib(ll n, ll mod) { // call me (result), modify this function for different applications
    vector<vector<ll>> Z = {{1, 1}, {1, 0}};
    ll f = n-1;
    if (n > 2) {
        vector<vector<ll>> mp = mat_pow(Z, n-2, mod);
        f = mp[0][0]*1 + mp[0][1]*0;
    }
    return f;
}
///////////////////// stop yanking /////////////////////

int main() {
    ll n, mod;
    cin >> n >> mod;
    cout << fib(n, mod); // called
    return 0;
}
