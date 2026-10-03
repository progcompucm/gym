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
#define pv(v) for(auto x : v) cout << x << " "; cout << endl;
#define pvi(v, alias) for(ll i = 0; i < v.size(); i++) cout << alias << "[" << i << "]" << " = " << v[i] << "\n";

template <typename T, typename... V>
void p(T&& t, V&&... v){
    cout << t;
    initializer_list<int>{ (cout << ' ' << v, 0)... };
    cout << endl;
}

struct Graph{
    ll N, LOG;
    vector<vll> adj, up;
    vll dep;

    Graph(ll n) : 
        N(n),
        LOG(log2(n) + 1), 
        up(n, vll(LOG, 0)), 
        dep(n, 0), 
        adj(n){}

    void add_edge(ll u, ll v){
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void dfs(ll node, ll parent){
        up[node][0] = parent;
        dep[node] = dep[parent] + 1;

        for(ll i = 1; i < LOG; i++){
            up[node][i] = up[up[node][i - 1]][i - 1];
        }

        for(ll v : adj[node]){
            if(v == parent) continue;
            dfs(v, node);
        }
    }

    ll lca(ll u, ll v){
        if(dep[u] < dep[v]) swap(u, v);
        ll diff = dep[u] - dep[v];

        for(ll i = 0; i < LOG; i++){
            if(diff & (1LL << i)) u = up[u][i];
        }

        if(u == v) return u;
        for(ll j = LOG - 1; j >= 0; j--){
            if(up[u][j] != up[v][j]){
                u = up[u][j];
                v = up[v][j];
            }
        }
        
        return up[u][0];
    }
};

void solve(){
    ll n;
    cin >> n;
    
    Graph g(n + 1);
    for(ll i = 0; i < n - 1; i++){
        ll u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }

    g.dfs(1, 0);
    p("Depth of nodes:");
    pvi(g.dep, "g.dep");
    
    p("LCA(9, 12):", g.lca(9, 12));
    p("LCA(10, 8):", g.lca(10, 8));
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