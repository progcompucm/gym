#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define F first
#define S second
#define pb push_back
#define pll pair<ll, ll>
#define vll vector<ll>
#define vvll vector<vll>
#define mpll map<pll, ll> 
#define mll map<ll, ll>
#define vpp vector<pll, pll>
#define qll queue<ll>
#define sz(x) ((ll)(x).size())
#define dedup_pair(a, b) { min(a, b), max(a, b) }
#define all(x) x.begin(), x.end()
#define rep(i, a, b) for (ll i = (a); i < (b); i++)
#define each(...) for (auto __VA_ARGS__)
#define endl "\n"

template <typename T, typename... V>
void p(T&& t, V&&... v){
    cout << t;
    initializer_list<int>{ (cout << v, 0)... };
}

ll n, m, maxsz;
vvll g;
bitset<1001> forbidden;
vll route;

// prunning
bool can_reach_target(ll start_node){
    if(start_node == 2 * n) return true;
    bitset<1001> vis;
    queue<ll> q;
    q.push(start_node);
    vis[start_node] = 1;
    while(!q.empty()){
        ll x = q.front();
        q.pop();
        if(x == 2 * n) return true;
        each(v : g[x]){
            if(forbidden[v] || vis[v]) continue;    
            vis[v] = 1;
            q.push(v);
        }
    }
    return false;
}

bool dfs(ll u){
    route.pb(u);
    if(u == 2 * n) return true;

    // if u is a lower floor sensor i, then i + N is forbidden
    ll partner = -1;
    if(u <= n){
        partner = u + n;
        forbidden[partner] = 1;
    }

    each(v : g[u]){
        if(forbidden[v]) continue;
        if(can_reach_target(v)){
            if(dfs(v)) return true;
        }
    }

    // backtrack
    if(u <= n){
        forbidden[partner] = 0;
    }
    route.pop_back();
    return false;
}

void solve(){
    cin >> n >> m;
    g.resize(2 * n + 1);

    rep(i, 0, m){
        ll u, v;
        cin >> u >> v;
        g[u].pb(v);
    }

    // is 2 * N node reachable?
    if(!can_reach_target(1)){
        cout << "*" << "\n";
        return;
    }

    if(dfs(1)){
        cout << sz(route) << endl;
        each(r : route) cout << r << " ";
        cout << endl;
    }else{
        cout << "*\n";
    }

}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    solve();

    return 0;
}   