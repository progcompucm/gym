/**
There is an undirected star graph consisting of n nodes labeled from 1 to n. 
A star graph is a graph where there is one center node and exactly n - 1 edges that connect the center node with every other node.

You are given a 2D integer array edges where each edges[i] = [ui, vi] 
indicates that there is an edge between the nodes ui and vi. Return the center of the given star graph.

Constraints:
    3 <= n <= 10^5
    edges.length == n - 1
    edges[i].length == 2
    1 <= ui, vi <= n
    ui != vi
 */

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define F first
#define S second
#define pb push_back
#define pll pair<ll, ll>
#define vll vector<ll>
#define mpll map<pll, ll> 
#define mll map<ll, ll>
#define vpp vector<pll, pll>
#define sz(x) ((ll)) x.size()
#define all(x) x.begin(), x.end()
#define endl "\n"

template <typename T, typename... V>
void p(T&& t, V&&... v){
    cout << t;
    initializer_list<int>{ (cout << ' ' << v, 0)... };
    cout << endl;
}

void solve(){
    ll n, m;
    cin >> n >> m;
    
    vector<vll> adj(n + 1);
    for(ll i = 1; i <= m; i++){
        ll a, b;
        cin >> a >> b;
        // undirected
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    /*for(ll u = 1; u <= n; u++){
        cout << "u: " << u << " -> ";
        for(ll v : adj[u]){
            cout << v << " ";
        }
        cout << endl;
    }*/

    // we know that the rule is:
    // "one center node and exactly n - 1 edges that connect the center ..."
    // so, just check the len of conns for every node:
    for(ll u = 1; u <= n; u++){
        if(adj[u].size() == n - 1){
            cout << u << endl;
            return;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    
    ll t;
    cin >> t;
    while(t--) solve();

    return 0;
}