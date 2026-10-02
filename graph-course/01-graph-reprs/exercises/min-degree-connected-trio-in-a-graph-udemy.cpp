#include<bits/stdc++.h>
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
#define sz(x) x.size()
#define all(x) x.begin(), x.end()
#define endl "\n"

template <typename T, typename... V>
void p(T&& t, V&&... v){
    cout << t;
    initializer_list<int>{ (cout << ' ' << v, 0)... };
    cout << endl;
}

int minTrioDegree(int n, vector<vector<int>> edges){
    // a connected trio is a set of three nodes
    // where there is an edge between every pair of them
    // and the degree is the num of edges where
    // one endpoint is in the trio and the other is not
    vector<vll> adj(n + 1);
    vector<vector<bool>> conn(n + 1, vector<bool>(n + 1, false));
    for(ll i = 0; i < edges.size(); i++){
        auto e = edges[i];
        ll u = e[0], v = e[1];
        adj[u].pb(v);
        adj[v].pb(u);
        conn[u][v] = true;
        conn[v][u] = true;
    }
    
    ll min_degree = LLONG_MAX;
    for(ll u = 1; u <= n; u++){
        for(ll v = u + 1; v <= n; v++){
            if(!conn[u][v]) continue;
            for(ll w = v + 1; w <= n; w++){
                /*p("u:", u, "v:", v, "w:", w);
                p("conn[", u, "][", v, "]:", conn[u][v]);
                p("conn[", u, "][", w, "]:", conn[u][w]);
                p("conn[", v, "][", w, "]:", conn[v][w]);*/

                if(!conn[u][w] || !conn[v][w]) continue;
                ll deg = sz(adj[u]) + sz(adj[v]) + sz(adj[w]) - 6;
                min_degree = min(min_degree, deg);
            }
        }
    }

    if(min_degree == LLONG_MAX) return -1;
    return min_degree;
}

int main(){
    vector<vector<int>> edges = {
        {1, 2}, {1, 3}, {3, 2}, {4, 1}, {5, 2}, {3, 6}
    };
    cout << minTrioDegree(6, edges);
    return 0;
}