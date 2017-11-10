#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(log(m))

///////////////////// start yanking ////////////////////
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1, gcd = exgcd(b, a%b, x1, y1);
    x = y1;
    y = x1-y1*(a/b);
    return gcd;
}

ll invmod(ll a, ll m) {
    ll x, y;
    ll gcd = exgcd(a, m, x ,y);
    assert(gcd == 1);
    x = (x % m + m) % m;
    return x;
}
///////////////////// stop yanking /////////////////////

/*
 * Notes:
 * A*X = 1 (%m)
 * or,
 * (A*X)%m = 1
 * A and m given, find X
 * X exists iff gcd(A,m)=1 (relatively prime)
 * range(X) = {0,1,2,...,m-1} (0 is invalid)
 * method - extended euclid
 * Ax + By = gcd(A,B) -> Ax + My = 1
 * (A/B)%C = (A*modinv(B,C))%C
 */

int main() {
    ll a, m;
    cin >> a >> m;
    cout << invmod(a, m);
    return 0;
}
