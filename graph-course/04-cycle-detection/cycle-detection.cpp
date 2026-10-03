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

struct Graph{
    ll N;
    vector<vll> adj;

    Graph(ll n) : N(n), adj(n){}

    void add_edge(ll u, ll v){
        adj[u].pb(v);
        adj[v].pb(u);
    }

    bool dfs(ll node, vector<bool>& vis, ll parent){
        vis[node] = true;
        for(ll v : adj[node]){
            if(!vis[v]){
                vis[v] = true;
                bool nbr_found_a_cycle = dfs(v, vis, node);
                if(nbr_found_a_cycle) return true;
                continue;
            }

            if(v != parent) return true;
        }
        return false;
    }

    bool contains_cycle(){
        vector<bool> vis(N, false);
        return dfs(0, vis, -1);
    }
};

void solve(){
    ll n, m;
    cin >> n >> m;
    
    Graph g(n);
    for(ll i = 0; i < m; i++){
        ll u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }

    bool has_cycle = g.contains_cycle();
    if(has_cycle){
        cout << "has cycle\n";
    }else{
        cout << "no cycle\n";
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