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

    map<ll, map<ll, vll>> gr;
    map<ll, vll> nbc;
    rep(i, 0, m){
        ll u, v, c;
        cin >> u >> v >> c;
        gr[c][u].pb(v);
        gr[c][v].pb(u);
        nbc[u].pb(c);
        nbc[v].pb(c);
    }

    if(sz(gr) < 2) return p("0\n");

    ll ans = 0;
    set<pll> dangerous;

    each([ color, nodes ] : gr){
        each([ u, neighs ] : nodes){
            each(v : neighs){
                if(sz(nbc[v]) < 2) continue;
                each(v_color : nbc[v]){
                    if(v_color == color) continue;
                    each([other_u, other_neighs] : gr[color]){
                        if(other_u == v) continue;
                        if(gr[v_color].count(other_u) == 0) continue;
                        dangerous.insert(dedup_pair(color, v_color));
                    }
                }
            }
        }
    }

    cout << sz(dangerous) << "\n";
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