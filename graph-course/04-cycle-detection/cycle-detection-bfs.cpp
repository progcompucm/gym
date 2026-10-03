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

    bool contains_cycle(ll root_node){
        vector<ll> parent(N, -1);
        queue<ll> q;
        parent[root_node] = root_node;
        q.push(root_node);
        while(!q.empty()){
            ll u = q.front();
            q.pop();
            for(ll v : adj[u]){
                if(parent[v] == -1){
                    parent[v] = u;
                    q.push(v);
                }else if(v != parent[u]){
                    return true;
                }
            }
        }
        return false;
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

    bool has_cycle = g.contains_cycle(0);
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