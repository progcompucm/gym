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
#define all(x) x.begin(), x.end()
#define rep(i, a, b) for (ll i = (a); i < (b); i++)
#define each(a, b) for (auto a : b)
#define endl "\n"

template <typename T, typename... V>
void p(T&& t, V&&... v){
    cout << t;
    initializer_list<int>{ (cout << v, 0)... };
    cout << endl;
}

void solve(){
    ll n, m;
    cin >> n >> m;

    vvll g(n + 1);
    mpll c;
    rep(i, 0, m){
        ll ui, vi, ci;
        cin >> ui >> vi >> ci;
        c[{ ui, vi }] = ci;
        c[{ vi, ui }] = ci;
        g[ui].pb(vi);
        g[vi].pb(ui);
    }

    vvll circuits;
    vector<bool> vis(n + 1, false);
    ll u = 1;
    vis[u] = true;
    each(v, g[u]){
        vis[v] = true;
        circuits.pb({ u, v });
        each(v_neigh, g[v]){
            if(v_neigh == u) continue;
            qll q;
            q.push(v_neigh);
            vll path = { u, v };
            vis[v_neigh] = true;

            while(!q.empty()){
                ll x = q.front();
                q.pop();
                path.pb(x);
                each(neigh, g[x]){
                    if(u != neigh && vis[neigh]) continue;
                    if(u == neigh){
                        path.pb(u);
                        circuits.pb(path);
                        path = { u, v, x };
                        continue;
                    }
                    vis[neigh] = true;
                    q.push(neigh);
                }
            }
        }
    }

    ll ans = 0;
    each(loop, circuits){
        set<ll> colors;
        rep(j, 0, sz(loop) - 1){
            if(sz(colors) >= 2){
                ans++;
                break;
            }
            ll u = loop[j], v = loop[j + 1];
            colors.insert(c[{ u, v }]);
        }
    }
    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
   
    solve();

    return 0;
}