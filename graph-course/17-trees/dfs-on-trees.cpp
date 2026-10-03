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

template <typename T, typename... V>
void p(T&& t, V&&... v){
    cout << t;
    initializer_list<int>{ (cout << ' ' << v, 0)... };
    cout << endl;
}

void dfs(ll node, ll parent, vector<vll>& adj, vll& parent_node){
    parent_node[node] = parent;
    for(ll v : adj[node]){
        if(v == parent) continue;
        dfs(v, node, adj, parent_node);
    }
}

// all ancestors
vll get_path(ll from, ll to, vector<vll>& adj){
    ll n = adj.size();
    vll parent(n, -1);
    dfs(from, -1, adj, parent);
    
    vll path;
    while(to != -1){
        path.pb(to);
        if(to == from) break;
        to = parent[to];
    }
    reverse(all(path));
    return path;
}

void solve(){
    ll n;
    cin >> n;

    vector<vll> adj(n + 1);
    vll p(n + 1);

    for(ll i = 0; i < n - 1; i++){
        ll u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    
    auto path = get_path(1, 5, adj);
    pv(path);
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