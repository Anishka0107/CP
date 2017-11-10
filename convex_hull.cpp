#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// For a set of points on a plane, convex hull is the smallest convex polygon that contains all these points
// Graham Scan Algorithm (not optimal but simpler, better - Chan's algorithm runs in O(n*log(h)))
// TC: O(n*log(n))

///////////////////// start yanking ////////////////////
template<class T>
struct point {
    T x, y;
};

template<class T>
bool scomp(const point<T> &a, const point<T> &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

template<class T>
bool clockwise(const point<T> &a, const point<T> &b, const point<T> &c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

template<class T>
bool anticlockwise(const point<T> &a, const point<T> &b, const point<T> &c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

template<class T>
vector<point<T>> convex_hull(vector<point<T>> &points) {
    vector<point<T>> ch;
    if (points.size() == 1) {
        return ch;
    }
    sort(points.begin(), points.end(), scomp<T>);
    point<T> p1 = points[0], p2 = points[points.size()-1];
    vector<point<T>> up = {p1}, down = {p1};
    for (ll i = 1; i < points.size(); i++) {
        if (i == points.size()-1 || clockwise(p1, points[i], p2)) {
            while (up.size() >= 2 && !clockwise(up[up.size()-2], up[up.size()-1], points[i])) {
                up.pop_back();
            }
            up.push_back(points[i]);
        }
        if (i == points.size()-1 || anticlockwise(p1, points[i], p2)) {
            while(down.size() >= 2 && !anticlockwise(down[down.size()-2], down[down.size()-1], points[i])) {
                down.pop_back();
            }
            down.push_back(points[i]);
        }
    }
    for (ll i = 0; i < up.size(); i++) {
        ch.push_back(up[i]);
    }
    for (ll i = down.size()-2; i > 0; i--) {
        ch.push_back(down[i]);
    }
    return ch;
}
///////////////////// stop yanking /////////////////////

int main() {
    ll n;
    cin >> n;
    vector<point<ll>> points(n);
    for (ll i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    auto ch = convex_hull(points);
    for (auto &pt : ch) {
        cout << pt.x << " " << pt.y << "\n";
    }
    return 0;
}
