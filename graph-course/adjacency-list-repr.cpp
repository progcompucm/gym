// i think that this is not for competivie programming but can be helpful...

#include <bits/stdc++.h>
using namespace std;

#define ll long long

class Graph{
    ll N;
    list<ll> *l;

public:
    Graph(ll n){
        N = n;
        l = new list<ll>[N];
    }

    void add_edge(ll u, ll v, bool undir = true){
        l[u].push_back(v);
        if(undir) l[v].push_back(u);
    }

    void print(){
        for(ll u = 0; u < N; u++){
            cout << u << " -> ";
            for(ll v : l[u]) cout << v << " ";
            cout << "\n";
        }
    }
};

int main(){
    Graph g(6);
    g.add_edge(0, 1);
    g.add_edge(0, 4);
    g.add_edge(2, 1);
    g.add_edge(3, 4);
    g.add_edge(4, 5);
    g.add_edge(2, 3);
    g.add_edge(3, 5);

    g.print();

    return 0;
}
