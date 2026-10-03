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
        set<pll> s;
        vll parent(N, -1);

        dist[src] = 0;
        s.insert({ 0, src });

        while(!s.empty()){
            auto it = s.begin();
            ll node = it->second;
            ll curr_dist = it->first;
            s.erase(it); 

            for(auto [v, w] : adj[node]){
                if(curr_dist + w < dist[v]){
                    // remove if neighbor already exists in the set
                    auto f = s.find({ dist[v], v });
                    if(f != s.end()) s.erase(f);
                    // insert the updated value with the new dist
                    dist[v] = curr_dist + w;
                    parent[v] = node;
                    s.insert({ dist[v], v });
                }
            }
        }
        
        vll path;
        ll curr = dest;
        while(curr != -1){
            path.pb(curr);
            curr = parent[curr];
        }

        reverse(all(path));

        for(ll n : path){
            cout << n << " ";
        }
        cout << "\n";
        
        return dist[dest];
    }
};

void solve(){
    ll n, m;
    cin >> n >> m;
    
    Graph g(n + 1);
    for(ll i = 0; i < m; i++){
        ll u, v, w;
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }

    ll dist = g.dijkstra(1, n);
    cout << dist << "\n";
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