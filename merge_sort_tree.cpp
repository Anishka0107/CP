#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Query: For range [i, j] (1-indexed) and k, output number of values in array in that range less than k
// This implementation is for online queries using merge sort tree (brother of segtree), TC: O(n*log(n)) for precomputation, O(log(n)*log(n)) per query
// Can be solved offline using segment tree in O((n+q)*log(n+q)) by sorting both array's elements and query's k together
// Segment tree can be used for keeping count of elements greater than particular k, leaf nodes of segtree will be 0 or 1 indicating smaller or greater than current k
// Iterate over sorted array in reverse manner, if it's an array element then perform point update for that position in segment tree (corresponding leaf node set to 1), if it's a query then query over segment tree for that range

///////////////////// start yanking ////////////////////
const int N = 1000000;
int arr[N];
vector<int> mst[4*N]; 
 
void build(int start, int end, int num) { // call me (precomputation)
    if (start == end) {
        mst[num].push_back(arr[start]);
        return;
    }
    int mid = start + (end-start)/2;
    build(start, mid, 2*num+1);
    build(mid+1, end, 2*num+2);
    merge(mst[2*num+1].begin(), mst[2*num+1].end(), mst[2*num+2].begin(), mst[2*num+2].end(), back_inserter(mst[num]));
}

int query_range(int start, int end, const int l, const int r, const int k, int num) { // call me (result)
    if (l > end || r < start) { 
        return 0;
    }
    if (l <= start && r >= end) {
        return lower_bound(mst[num].begin(), mst[num].end(), k) - mst[num].begin();
    }
    int mid = start + (end-start)/2;
    return query_range(start, mid, l, r, k, 2*num+1) + query_range(mid+1, end, l, r, k, 2*num+2);
}
///////////////////// stop yanking /////////////////////

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    build(0, n-1, 0); // called
    cout << endl;
    int q;
    cin >> q;
    while (q--) {
        int left, right, k;
        cin >> left >> right >> k;
        cout << query_range(0, n-1, left-1, right-1, k, 0) << "\n"; // called
    }
    return 0;
}
