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

    vvll nodes(m + 1);
    vvll nbc(n + 1);
    rep(i, 0, m){
        ll u, v, c;
        cin >> u >> v >> c;
        nodes[c].pb(u);
        nodes[c].pb(v);
        nbc[u].pb(c);
        nbc[v].pb(c);
    }

    rep(c, 1, m + 1){
        sort(all(nodes[c]));
        nodes[c].erase(unique(all(nodes[c])), nodes[c].end());
    }

    rep(u, 1, n + 1){
        sort(all(nbc[u]));
        nbc[u].erase(unique(all(nbc[u])), nbc[u].end());
    }

    ll ans = 0;
    vll cnt(m + 1, 0);

    rep(color, 1, m + 1){
        vll seen;
        each(u : nodes[color]){
            each(other : nbc[u]){
                if(other <= color) continue; 
                if(cnt[other] == 0) seen.pb(other);
                cnt[other]++;
                if(cnt[other] == 2) ans++; 
            }
        }
        each(f : seen) cnt[f] = 0;
    }

    cout << ans << "\n";
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