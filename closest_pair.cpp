#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

// Using the line sweep technique
// Points represented as pairs: first->y, second->x, to facilitate storage in set and sorting by y
// TC: O(n*log(n))

///////////////////// start yanking ////////////////////
template<class T>
bool scomp(const pair<T, T> &a, const pair<T, T> &b) { // for vector
    return a.second < b.second;
}

template<class T>
ld closest_pair(vector<pair<T, T>> &points, pair<T, T> &p1, pair<T, T> &p2) {
    sort(points.begin(), points.end(), scomp<T>);
    ld closest = LDBL_MAX;
    set<pair<T, T>> sp = {points[0]};
    ll left = 0;
    for (ll i = 1; i < points.size(); i++) {
        while (left < i && points[i].second-points[left].second > closest) {
            sp.erase(points[left++]);
        }
        for (auto it = sp.lower_bound({points[i].first-closest, points[i].second-closest}); it != sp.end() && points[i].first+closest >= it->first; it++) {
            ld curr = sqrtl(powl(points[i].first - it->first, 2) + powl(points[i].second - it->second, 2));
            if (closest > curr) {
                closest = curr;
                p1 = *it, p2 = points[i];
            }
        }
        sp.insert(points[i]);
    }
    return closest;
}
///////////////////// stop yanking /////////////////////

int main() {
    ll n;
    cin >> n;
    vector<pair<ld, ld>> points(n);
    for (ll i = 0; i < n; i++) {
        cin >> points[i].second >> points[i].first;
    }
    pair<ld, ld> p1, p2;
    cout << closest_pair(points, p1, p2) << "\n"; // called
    cout << p1.second << " " << p1.first << " " << p2.second << " " << p2.first << "\n";
    return 0;
}
