#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

///////////////////// start yanking ////////////////////
const int N = 1000000;
int arr[N], st[4*N], lazy[4*N]; 
 
void build(int start, int end, int num) { // call me (precomputation)
    if (start == end) {
        st[num] = arr[start];
        return;
    }
    int mid = start + (end-start)/2;
    build(start, mid, 2*num+1);
    build(mid+1, end, 2*num+2);
    st[num] = st[2*num+1] + st[2*num+2];
}

int query_range(int start, int end, const int l, const int r, int num) { // call me (result)
    if (lazy[num] != 0) {
        st[num] += (end-start+1)*lazy[num];
        if (start != end) {
            lazy[2*num+1] += lazy[num];
            lazy[2*num+2] += lazy[num];
        }
        lazy[num] = 0;
    }
    if (l > end || r < start) {
        return 0;
    }
    if (l <= start && r >= end) {
        return st[num];
    }
    int mid = start + (end-start)/2;
    return query_range(start, mid, l, r, 2*num+1) + query_range(mid+1, end, l, r, 2*num+2);
}

void update_lazy(int start, int end, const int upd, const int l, const int r, int num) { // increments by upd; to set to upd, change += to =// call me (result)
    if(lazy[num] != 0) {
        st[num] += (end-start+1)*lazy[num];
	    if(start != end) {
            lazy[2*num+1] += lazy[num];
            lazy[2*num+2] += lazy[num];
        }
        lazy[num] = 0;
    }
    if(l>end || r<start)
        return;
    if(l<=start && r>=end) {
        st[num] += (end-start+1)*upd;
        if(start != end) {
            lazy[2*num+1] += upd;
            lazy[2*num+2] += upd;
        }
        return;
    }
    int mid = start + (end-start)/2;
    update_lazy(start, mid, upd, l, r, 2*num+1);
    update_lazy(mid+1, end, upd, l, r, 2*num+2);
    st[num] = st[2*num+1] + st[2*num+2];
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
    while (true) {
        int ch;
        cin >> ch;
        int left, right;
        cin >> left >> right;
        switch (ch) {
            case 1: 
                cout << query_range(0, n-1, left-1, right-1, 0) << "\n"; // called
                break;
            case 2:
                int upd;
                cin >> upd;
                update_lazy(0, n-1, upd, left-1, right-1, 0); // called
                break;
            default:
                return 0;
        }
    }
    return 0;
}
