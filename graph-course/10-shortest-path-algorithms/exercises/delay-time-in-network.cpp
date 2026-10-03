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

template <typename T, typename... V>
void p(T&& t, V&&... v){
    cout << t;
    initializer_list<int>{ (cout << ' ' << v, 0)... };
    cout << endl;
}

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
    ll n, m, k;
    cin >> n >> m >> k;
    
    Graph g(n + 1);
    for(ll i = 0; i < m; i++){
        ll u, v, w;
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }

    auto dist = g.floyd_warshall();
    ll ans = -1;
    for(ll i = k; i < g.N; i++){
        for(ll j = k; j < g.N; j++){
            if(dist[i][j] == 0) continue;
            ans = max(ans, dist[i][j]);
        }
    }

    cout << ans;
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