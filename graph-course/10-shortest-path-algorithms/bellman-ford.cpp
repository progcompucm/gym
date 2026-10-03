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
#define endl "\n"

struct Edge{
    ll u, v, w;
};

struct Graph{
    ll N;
    vector<Edge> e;

    Graph(ll n) : N(n){}

    void add_edge(ll u, ll v, ll w){
        e.push_back({ u, v, w });
    }

    vll bellman_ford(ll src){
        vll dist(N, LLONG_MAX);
        dist[src] = 0;
        for(ll i = 0; i < N - 1; i++){
            for(auto [u, v, w] : e){
                if(dist[u] == LLONG_MAX) continue;
                dist[v] = min(dist[v], dist[u] + w);
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