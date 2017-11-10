#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

///////////////////// start yanking ////////////////////
// single combination only - preferably for small n and k, with no need of mod, TC: O(k), SC: O(1)
ll C(ll n, ll k) {
    ll result = 1;
    k = (k > n-k) ? (n-k) : k;
    for (ll i = 0; i < k; i++) {
        result *= (n-i);
        result /= (i+1);    
    }
    return result;
}


// multiple combinations, large n and k with larger prime mod, TC: O(n), SC: O(n)
const int N = 10000000;
ll fact[N+1], invfact[N+1], modinv[N+1];

void calculate_mod_inverse(ll n, ll mod) {
    modinv[0] = modinv[1] = 1;
    for (ll i = 2; i <= n; i++) {
        modinv[i] = modinv[mod%i] * (mod - mod/i) % mod;
    }
}

void calc_fact(ll n, ll mod) {
    fact[0] = 1;
    for (ll i = 1; i <= n; i++) {
        fact[i] = (fact[i-1] * i) % mod;
    }
}

void calc_invfact(ll n, ll mod) {
    invfact[0] = 1;
    for (ll i = 1; i <= n; i++) {
        invfact[i] = (invfact[i-1] * modinv[i]) % mod;
    }
}

void build_all_combs(ll n, ll k, ll mod) { // call me (precomputation)
    assert(n >= k);
    assert(n <= N);
    calc_fact(n, mod);
    calculate_mod_inverse(n, mod);
    calc_invfact(n, mod);
}

ll C(ll n, ll k, ll mod) { // call me (result)
    assert(n >= k);
    assert(n <= N);
    return ((fact[n]%mod) * ((invfact[n-k]*invfact[k])%mod)) % mod;
}


// Lucas theorem (TC: O(mod*mod*logmod(n)), SC: O(mod)), mod is any small prime, for few queries
ll baseC(ll n, ll k, ll mod) {
    ll comb[k+1] = {0};
    comb[0] = 1;
    for (ll i = 1; i <= n; i++) {
        for (ll j = min(i, k); j > 0; j--) {
            comb[j] = (comb[j] + comb[j-1]) % mod;
        }
    }
    return comb[k];
}

ll CL(ll n, ll k, ll mod) { // call me (result)
    if (k == 0) {
        return 1;
    }
    ll ni = n%mod, ki = k%mod;
    return (CL(n/mod, k/mod, mod) * baseC(ni, ki, mod)) % mod;
}


// Lucas theorem 2 (TC: O(mod*mod+q*logmod(n)) O(mod*mod) for precomputation, O(logmod(n)) for each query, SC: O(mod*mod)), mod is a small prime, for more queries
const int MOD = 1000;
ll comb[MOD+1][MOD+1] = {0};

void baseCQ(ll mod) { // call me (precomputation)
    for (ll i = 0; i <= mod; i++) {
        for (ll j = 0; j <= i; j++) {
            if (i == j || j == 0) {
                comb[i][j] = 1;
            } else {
                comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
            }
        }
    }
}

ll CLQ(ll n, ll k, ll mod) { // call me (result)
    if (k == 0) {
        return 1;
    }
    ll ni = n%mod, ki = k%mod;
    return (CLQ(n/mod, k/mod, mod) * comb[ni][ki]) % mod;
}


// when mod is not prime, find its prime factorization and use CRT
vector<pair<ll, ll>> prime_factors; // first = prime factor, second = powered prime factor

void get_prime_factors(ll n) {
    prime_factors.clear();
    for (ll i = 2; i <= sqrt(n); i++) {
        if (n%i == 0) {
            ll prod = 1;
            while (n%i == 0) {
                prod *= i;
                n /= i;
            }
            prime_factors.push_back({i, prod});
        }
    }
    if (n > 2) {
        prime_factors.push_back({n, n});
    }
}

ll modpow(ll b, ll e, ll m) {
    ll result = 1;
    while (e > 0) {
        if (e & 1) {
            result = (result * b) % m;
        }
        e >>= 1;
        b = (b * b) % m;
    }
    return result;
}

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

vector<ll> remainders, G;

void calc_G(ll n, ll maxval) {
    G.resize(maxval+1);
    G[0] = G[1] = 1;
    for (ll i = 2; i <= maxval; i++) {
        if (i%n) {
            G[i] = (G[i-1]*i) % maxval;
        } else {
            G[i] = G[i-1];
        }
    }
}

ll calc_E(ll n, ll p) {
    ll ret = 0;
    while (n) {
        ret += n/p;
        n /= p;
    }
    return ret;
}
 
ll calc_f(ll n, ll whole) {
    return modpow(G[whole-1], n/whole, whole) * G[n%whole];
}
 
ll calc_F(ll n, ll p, ll whole) {
    ll ret = 1, i = 1;
    while (i <= n) {
        ret = (ret * calc_f(n/i, whole)) % whole;
        i *= p;
    }
    return ret;
}

ll LC(ll n, ll k, ll p, ll whole) {
    ll h = calc_E(n, p) - calc_E(k, p) - calc_E(n-k, p), h1 = calc_F(n, p, whole), h2 = invmod((calc_F(k, p, whole) * calc_F(n-k, p, whole)) % whole, whole);
    return (((modpow(p, h, whole) * h1) % whole) * h2) % whole;
}

void get_remainders(ll n, ll k, ll mod) {
    for (int i = 0; i < prime_factors.size(); i++) {
        calc_G(prime_factors[i].first, prime_factors[i].second);
        remainders.push_back(LC(n, k, prime_factors[i].first, prime_factors[i].second));
    }
}

ll get_CRT(ll mod) {
    ll prod = mod;
    ll result = 0;
    for (ll i = 0; i < prime_factors.size(); i++) {
        ll pd = prod / prime_factors[i].second;
        result += remainders[i] * invmod(pd, prime_factors[i].second) * pd;
    }
    return result % prod;
}

ll Cspecial(ll n, ll k, ll mod) { // call me (result)
    get_prime_factors(mod);
    get_remainders(n, k, mod);
    return get_CRT(mod);
}
///////////////////// stop yanking /////////////////////

int main() {
    ll n, k, mod;
    cin >> n >> k >> mod;
    build_all_combs(n, k, mod);
    cout << C(n, k, mod);
    cout << "\n" << CL(n, k, mod);
    baseCQ(mod);
    cout << "\n" << CLQ(n, k, mod);
    cout << "\n" << Cspecial(n, k, mod);
    return 0;
}
