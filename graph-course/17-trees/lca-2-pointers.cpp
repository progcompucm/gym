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
    ll N;
    vector<vll> adj;
    vll p, dep;

    Graph(ll n) : N(n + 1), p(n + 1, -1), dep(n + 1, 0), adj(n + 1){}

    void add_edge(ll u, ll v){
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void dfs(ll node, ll parent){
        p[node] = parent;
        dep[node] = dep[parent] + 1;
        for(ll v : adj[node]){
            if(v == parent) continue;
            dfs(v, node);
        }
    }

    ll lca(ll u, ll v){
        if(u == v) return u;
        // depth of u is more than depth of v,
        // for avoid 2 cases:
        if(dep[u] < dep[v]) swap(u, v);
        ll diff = dep[u] - dep[v];

        // depth of both nodes same
        while(diff--){
            u = p[u];
        }

        // until they are equal nodes keep climbing
        while(u != v){
            u = p[u];
            v = p[v];
        }

        return u;
    }
};

void solve(){
    ll n;
    cin >> n;
    
    Graph g(n);
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