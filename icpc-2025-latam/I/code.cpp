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

    ll vecsz = (2 * n) + 1;
    vector<vector<ll>> g(vecsz, vector<ll>());
    rep(i, 0, m){
        ll u, v;
        cin >> u >> v;
        g[u].pb(v);
    }

    auto idx = [&](ll u){
        return (u > n) ? (u - n) : (u + n);
    };

    bool found = false;
    vll p;
    each(neigh : g[1]){
        vector<bool> seen(vecsz, false);
        queue<ll> q;
        q.push(neigh);
        seen[1] = true;
        seen[idx(1)] = true;
        if(seen[neigh]) continue;
        p = vll(vecsz, -1);
        seen[neigh] = true;
        seen[idx(neigh)] = true;
        p[neigh] = 1;
        p[1] = 0;
        while(!q.empty()){
            ll x = q.front();
            q.pop();
            if(x == 2 * n){
                found = true;
                break;
            }
            each(v : g[x]){
                if(seen[v]) continue;
                seen[v] = true;
                seen[idx(v)] = true ;
                p[v] = x;
                q.push(v);
            }
        } 
        if(found) break;
    }
    if(!found){
        cout << "*\n";
        return;
    }
    ll curr = 2 * n;
    vll route;
    while(curr != 0){
        route.pb(curr);
        curr = p[curr];
    }
    reverse(all(route));
    cout << sz(route) << endl;
    each(r : route){
        cout << r << " ";
    }
    cout << endl;
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