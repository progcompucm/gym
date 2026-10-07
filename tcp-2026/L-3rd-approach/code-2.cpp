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

void solve(){
    ll n, m;
    cin >> n >> m;

    vvll nodes(m + 1), colors_by_node(n + 1);
    for(ll i = 0; i < m; i++){
        ll u, v, c;
        cin >> u >> v >> c;
        nodes[c].pb(u);
        nodes[c].pb(v);
        colors_by_node[u].pb(c);
        colors_by_node[v].pb(c);
    }

    rep(u, 1, m + 1){
        sort(all(nodes[u]));
        nodes[u].erase(unique(all(nodes[u])), nodes[u].end());
    }

    rep(c, 1, n + 1){
        sort(all(colors_by_node[c]));
        colors_by_node[c].erase(unique(all(colors_by_node[c])), colors_by_node[c].end());
    }
    
    vll cnt(m + 1, 0);
    ll ans = 0;
    rep(k, 1, m + 1){
        vll seen;   
        each(node : nodes[k]){
            each(l : colors_by_node[node]){
                if(l <= k) continue;
                if(cnt[l] == 0) seen.pb(l);
                cnt[l]++;
                if(cnt[l] == 2) ans++;
            }
        }
        each(node : seen) cnt[node] = 0;
    }

    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
   
    solve();

    return 0;
}