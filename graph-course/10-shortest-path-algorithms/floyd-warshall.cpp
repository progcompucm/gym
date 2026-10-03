#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define F first
#define S second
#define pb push_back
#define pll pair<ll, ll>
#define vll vector<ll>
#define vpll vector<pair<ll, ll>>
#define mpll map<pll, ll> 
#define mll map<ll, ll>
#define vpp vector<pll, pll>
#define sz(x) ((ll)) x.size()
#define all(x) x.begin(), x.end()
#define INF LLONG_MAX / 2
#define endl "\n"

struct Graph{
    ll N;
    vector<vll> adj;

    Graph(ll n) : N(n), adj(n, vector<ll>(n, INF)){
        for(ll i = 0; i < N; i++) adj[i][i] = 0;
    }

    void add_edge(ll u, ll v, ll w){
        adj[u][v] = min(adj[u][v], w);
        adj[v][u] = min(adj[v][u], w);
    }

    vector<vll> floyd_warshall(){
        vector<vll> dist = adj;
        for(ll k = 0; k < N; k++){
            for(ll i = 0; i < N; i++){
                for(ll j = 0; j < N; j++){
                    if(dist[i][k] == INF || dist[k][j] == INF) continue;
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        return dist;
    }
};


void solve(){
    ll n, m;
    cin >> n >> m;
    
    Graph g(n);
    for(ll i = 0; i < m; i++){
        ll u, v, w;
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
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