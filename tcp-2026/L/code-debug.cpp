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
#define sz(x) ((ll)) x.size()
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

    rep(i, 1, n + 1){
        cout << "g[" << i << "] = [";
        each(neigh, g[i]){
            cout << neigh << ", ";
        }
        cout << "]\n";
    }

    each(pr, c){
        auto [edge, color] = pr;
        cout << "c[{ " << edge.first << ", " << edge.second << " }] = " << color << "\n";
    }

    vvll circuits;
    vector<bool> vis(n + 1, false);

    ll u = 1;
    each(v, g[u]){
        circuits.pb({ u, v });
        for(ll i = 0; i < g[v].size(); i++){
            ll v_neigh = g[v][i];
            if(v_neigh == u) continue;
            qll q;
            q.push(v_neigh);
            vll path = { u, v };
            vis[u] = true;
            vis[v] = true;
            vis[v_neigh] = true;

            cout << "****************\n";
            cout << "Base Path: ";
            each(val, path){
                cout << val << " - ";
            }
            cout << "\nNeighbors: ";
            each(val, g[v]){
                cout << val << " - ";
            }
            cout << "\n***************";

            while(!q.empty()){
                ll x = q.front();
                q.pop();
                path.pb(x);
                p("\n: x = ", x);
                cout << ": Path: ";
                each(val, path){
                    cout << val << " - ";
                }
                cout << "\n";
                cout << ": Neighbors: ";
                each(val, g[x]){
                    cout << val << ", ";
                }
                cout << "\n-------------\n";
                each(neigh, g[x]){
                    p(": neigh = ", neigh);
                    p("::: visited = ", vis[neigh]);
                    if(u != neigh && vis[neigh]) continue;
                    if(u == neigh){
                        path.pb(u);
                        cout << "==> Closed-Path: ";
                        each(val, path){
                            cout << val << " - ";
                        }
                        cout << "\n";
                        circuits.pb(path);
                        path = { u, v, x };
                        continue;
                    }
                    vis[neigh] = true;
                    q.push(neigh);
                }
                cout << "-------------\n";
            }
        }
    }
    p("Loops:");
    each(loop, circuits){
        each(val, loop){
            cout << val << " - ";
        }
        cout << "\n";
    }
    p("-------------");
    ll ans = 0;
    each(loop, circuits){
        set<ll> colors;
        rep(j, 0, loop.size() - 1){
            if(colors.size() >= 2){
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
   
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    
    solve();

    return 0;
}