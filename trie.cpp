#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// TC: O(len(s)), SC: O(avg(len(s))*num(s))

///////////////////// start yanking ////////////////////
const int SIZE = 26; // size of the alphabet set
const int FIRST_CHAR = (int)'a';

struct node {
    node* children[SIZE];
    ll num_words, num_prefixes;
    node() {
        for (int i = 0; i < SIZE; i++) {
            children[i] = NULL;
        }
        num_words = num_prefixes = 0;
    }
};

struct trie {
    node* root;
    trie() {
        root = new node();
    }
    void insert(const string &);
    int remove(const string &, node*, ll);
    pair<ll, ll> count(const string &); // first -> num_words, second -> num_prefixes
    bool search(const string &);
    void _traverse(string &, node*, ll);
    void traverse(const string &);
};

void trie::insert(const string &s) {
    node* curr = root;
    for (ll i = 0; i < s.length(); i++) {
        int idx = (int)s[i] - FIRST_CHAR;
        if (!(curr->children[idx])) {
            curr->children[idx] = new node();
        }
        curr->num_prefixes++;
        curr = curr->children[idx];
    }
    curr->num_prefixes++;
    curr->num_words++;
}

int trie::remove(const string &s, node* curr, ll curr_depth) {
    if (curr) {
        if (curr_depth == s.length()) {
            if (curr->num_words) {
                curr->num_words--;
                curr->num_prefixes--;
                if (!(curr->num_words)) {
                    for (int i = 0; i < SIZE; i++) {
                        if (curr->children[i]) {
                            return 1;
                        }
                    }
                    return 2;
                }
                return 1;
            }
        }
        else {
            int idx = (int)s[curr_depth] - FIRST_CHAR;
            int rem = remove(s, curr->children[idx], curr_depth+1);
            if (rem) {
                curr->num_prefixes--;
                if (rem == 2) {
                    delete curr->children[idx];
                    curr->children[idx] = NULL;
                    bool no_children = true;
                    for (int i = 0; i < SIZE; i++) {
                        if (curr->children[i]) {
                            no_children = false;
                            break;
                        }
                    }
                    if (!curr->num_words && no_children) {
                        return 2;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

pair<ll, ll> trie::count(const string &s) {
    node* curr = root;
    for (ll i = 0; i < s.length(); i++) {
        int idx = (int)s[i] - FIRST_CHAR;
        if (!(curr->children[idx])) {
            return {0, 0};
        }
        curr = curr->children[idx];
    }
    return {curr->num_words, curr->num_prefixes};
}

bool trie::search(const string &s) {
    auto p = count(s);
    return p.first;
}

void trie::_traverse(string &s, node* curr, ll curr_depth) {
    if (curr->num_words) {
        for (ll i = 0; i < curr_depth; i++) {
            cout << s[i];
        }
        cout << " ";
    }
    for (int i = 0; i < SIZE; i++) {
        s += "0";
        if (curr->children[i]) {
            s[curr_depth] = i + FIRST_CHAR;
            _traverse(s, curr->children[i], curr_depth+1);
        }
    }
}   

void trie::traverse(const string &s) {
    node* curr = root;
    for (ll i = 0; i < s.length(); i++) {
        int idx = (int)s[i] - FIRST_CHAR;
        if (!(curr->children[idx])) {
            return;
        }
        curr = curr->children[idx];
    }
    string ns = s;
    _traverse(ns, curr, ns.size());
}
///////////////////// stop yanking /////////////////////

int main() {
    trie t; // created
    ll q;
    cin >> q;
    while (q--) {
        int ch;
        cin >> ch;
        string s;
        cin >> s;
        if (ch == 1) {
            t.insert (s); // called
        } else if (ch == 2) {
            t.remove (s, t.root, 0); // called
        } else if (ch == 3) {
            if (t.search(s)) { // called
                cout << "yes";
            } else {
                cout << "no";
            }
            cout << "\n";
        } else if (ch == 4) {
            auto p = t.count(s); // called
            cout << p.first << " " << p.second << "\n";
        } else if (ch == 5) {
            t.traverse(s); // called
        }
    }
    return 0;
}
