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

    bool is_bipartite(){
        vector<ll> color(N, -1);
        for(ll root = 0; root < N; root++){
            if(color[root] != -1) continue;

            queue<ll> q;
            q.push(root);
            color[root] = 0;

            while(!q.empty()){
                ll u = q.front();
                q.pop();

                for(ll v : adj[u]){
                    if(color[v] == -1){
                        color[v] = 1 - color[u];
                        q.push(v);
                    }else if(color[v] == color[u]){
                        return false;
                    }
                }
            }
        }
        return true;
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

    bool is_bipartite = g.is_bipartite();
    if(is_bipartite){
        cout << "is_bipartite\n";
    }else{
        cout << "no bipartite\n";
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