#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(n), SC: O(max(arr[1..n]))
// Counting sort

///////////////////// start yanking ////////////////////
void counting_sort(ll arr[], ll narr[], ll n) {
    ll m = *max_element(arr, arr+n);
    ll count[m+1] = {0};
    for (ll i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    for (ll i = 1; i <= m; i++) {
        count[i] += count[i-1];
    }
    for (ll i = 0; i < n; i++) {
        narr[count[arr[i]]-1] = arr[i];
        --count[arr[i]];
    }
}
///////////////////// stop yanking /////////////////////

int main() {
    ll n;
    cin >> n;
    ll arr[n], narr[n];
    for (ll i = 0; i < n; i++) {
        cin >> arr[i];
    }
    counting_sort(arr, narr, n);
    for (ll i = 0; i < n; i++) {
        cout << narr[i] << " ";
    }
    return 0;
}
