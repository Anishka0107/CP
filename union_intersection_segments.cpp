#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// TC: O(n*log(n)) for union, O(n) for intersection of segments with same slope

///////////////////// start yanking ////////////////////
vector<pair<ll, ll>> union_segments(vector<pair<ll, ll>> segment) { // call me (result)
    sort(segment.begin(), segment.end());
    ll index = 0;
    for (ll i = 0; i < segment.size(); i++) {
        if (index != 0 && segment[index-1].first <= segment[i].second) {
            while (index != 0 && segment[index-1].first <= segment[i].second) {
                segment[index-1].first = min(segment[index-1].first, segment[i].first);
                segment[index-1].second = max(segment[index-1].second, segment[i].second);
                index--;
            }
        } else {
            segment[index] = segment[i];
        }
        index++;
    }
    return {segment.begin(), segment.begin()+index};
}

bool ccomp(pair<ll, ll> p1, pair<ll, ll> p2) {
    return p1.second < p2.second;
}

pair<ll, ll> intersection_segments(vector<pair<ll, ll>> segment) { // call me (result)
    pair<ll, ll> is;
    is.first = (*max_element(segment.begin(), segment.end())).first;
    is.second = (*min_element(segment.begin(), segment.end(), ccomp)).second;
    if (is.first > is.second) {
        return {-1, -1};
    }
    return is;
}
///////////////////// stop yanking /////////////////////

int main() {
    ll n;
    cin >> n;
    vector<pair<ll, ll>> segment(n);
    for (ll i = 0; i < n; i++) {
        cin >> segment[i].first >> segment[i].second;
    }
    auto us = union_segments(segment); // called
    auto is = intersection_segments(segment); // called
    for (auto uu : us) {
        cout << uu.first << " " << uu.second << "\n";
    }
    if (is.first != -1) {
        cout << "\n" << is.first << " " << is.second;
    }
    return 0;
}
