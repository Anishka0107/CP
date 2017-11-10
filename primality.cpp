#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(sqrt(n))

///////////////////// start yanking ////////////////////
bool is_prime(ll n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n%2 == 0 || n%3 == 0) return false;
    for (int i = 5; i*i <= n; i += 6)
        if (n%i == 0 || n%(i+2) == 0) return false;
    return true;
}
///////////////////// stop yanking /////////////////////

int main() {
    ll n;
    cin >> n;
    cout << is_prime(n);
    return 0;
}
