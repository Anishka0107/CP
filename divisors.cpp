#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(sqrt(n))

///////////////////// start yanking ////////////////////
vector<ll> divisors;

void get_divisors(ll n) {
    deque<ll> dd;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n%i == 0) {
            divisors.push_back(i);
            if (n/i != i) {
                dd.push_front(n/i);
            }
        }
    }
    copy(dd.begin(), dd.end(), back_inserter(divisors));
}
///////////////////// stop yanking /////////////////////

int main() {
    ll n;
    cin >> n;
    get_divisors(n);
    for (int i = 0; i < divisors.size(); i++) {
        cout << divisors[i] << " ";
    }
    return 0;
}
