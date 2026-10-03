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

struct Graph{
    ll N;
    vector<vpll> adj;

    Graph(ll n) : N(n), adj(n){}

    void add_edge(ll u, ll v, ll w){
        adj[u].pb({ v, w });
        adj[v].pb({ u, w });
    }

    ll dijkstra(ll src, ll dest){
        vll dist(N, LLONG_MAX);
        priority_queue<pll, vpll, greater<pll>> pq;
        dist[src] = 0;
        pq.push({ 0, src });

        while(!pq.empty()){
            auto [curr_dist, u] = pq.top();
            pq.pop();

            if(curr_dist != dist[u]) continue;
            //if(u == dest) return curr_dist;
            
            for(auto [v, w] : adj[u]){
                ll new_dist = curr_dist + w;
                if(new_dist < dist[v]){
                    dist[v] = new_dist;
                    pq.push({ new_dist, v });
                }
            }
        }

        for(ll i = 0; i < N; i++){
            cout << "Node: " << i << " dist: " << dist[i] << "\n";
        }
        
        return -1;
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

    g.dijkstra(0, 2);
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