#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Range sum query with versions, TC: O(n*log(n)) for precomputation, O(log(n)) per query (any type), SC: O(q*log(n))

///////////////////// start yanking ////////////////////
const int N = 1000000;
const int MAXN = 10000000;
int arr[N], pst[MAXN], L[MAXN], R[MAXN], next_free; 

int build(int start, int end) { // call me (precomputation)
    if (start == end) {
        next_free++;
        pst[next_free] = arr[start];
        return next_free;
    }
    int mid = start + (end-start)/2;
    int retl = build(start, mid);
    int retr = build(mid+1, end);
    next_free++;
    L[next_free] = retl;
    R[next_free] = retr;
    pst[next_free] = pst[retl] + pst[retr];
    return next_free;
}

int query_range(int start, int end, const int l, const int r, int num) { // call me (result)
    if (l>end || r<start)
        return 0;
    if (l<=start && r>=end)
        return pst[num];
    int mid = start + (end-start)/2;
    return query_range(start, mid, l, r, L[num]) + query_range(mid+1, end, l, r, R[num]);
}

int update_point(int start, int end, const int i, const int k, int num) { // call me (result)
    if (start == end) {
        next_free++;
        pst[next_free] = pst[num] + k; // increment by k, to set values, set it to k directly
        return next_free;
    }
    int mid = start + (end-start)/2;
    if (i <= mid) {
        int retl = update_point(start, mid, i, k, L[num]);
        next_free++;
        L[next_free] = retl;
        R[next_free] = R[num];
        pst[next_free] = pst[retl] + pst[R[num]];
    } else {
        int retr = update_point(mid+1, end, i, k, R[num]);
        next_free++;
        L[next_free] = L[num];
        R[next_free] = retr;
        pst[next_free] = pst[L[num]] + pst[retr];
    }
    return next_free;
}
///////////////////// stop yanking /////////////////////

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<int> version;
    version.push_back(build(0, n-1)); // called
    cout << endl;
    int q;
    cin >> q;
    while (q--) {
        int ch;
        cin >> ch;
        if (ch == 1) {
            int left, right, ver;
            cin >> left >> right >> ver;
            cout << query_range(0, n-1, left-1, right-1, version[ver]) << "\n"; // called
        } else {
            int i, k;
            cin >> i >> k;
            version.push_back(update_point(0, n-1, i-1, k, version[version.size()-1])); // called
        }
    }
    return 0;
}
