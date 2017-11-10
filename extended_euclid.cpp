#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(log(min(a,b)))

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
///////////////////// stop yanking /////////////////////


/*
 * Notes:
 * Ax + By = gcd(A,B)
 * A,B given; find gcd(A,B),x,y
 *
 */

int main() {
    ll x, y, a, b;
    cin >> a >> b;
    ll gcd = exgcd(a, b, x, y);
    cout << "GCD = " << gcd << ", x = " << x << ", y = " << y;
    return 0;
}
