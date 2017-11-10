#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// use inbuilt __gcd(int a,int b) instead
// TC: O(log(min(a,b))) // not precise though, around log(a)*log(a) as % is not O(1)

///////////////////// start yanking ////////////////////
ll gcd(ll a, ll b) {
    if (a == 0)
        return b;
    return gcd(b%a, a);
}
///////////////////// stop yanking /////////////////////

int main() {
    ll a, b;
    cin >> a >> b;
    cout << gcd(a, b);
    return 0;
}
