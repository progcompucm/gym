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
    ll n;
    cin >> n;

    unordered_map<ll, ll> m;
    rep(i, 0, n){
        ll h;
        cin >> h;
        m[h]++;
    }

    if(m.size() < 2){
        p("0", endl);
        return;
    }

    vector<pll> v;
    each(&h : m){
        v.pb({ h.F, h.S });
    }

    sort(all(v), [](auto &a, auto &b){
        return a.S > b.S;
    });

    ll ans = 0, offset = 0;
    for(ll i = 0; i < sz(v) - 2; i += 3){
        while(v[i].S > 0){
            ll c = min(v[i].S, min(v[i + 1].S, v[i + 2].S));
            v[i].S -= c;
            v[i + 1].S -= c;
            v[i + 2].S -= c;
            ans += c;
            if(v[i].S == 0) break;
            if(v[i + 1].S == 0){
                swap(v[i + 1], v[sz(v) - 1 - offset]);
                offset++;
            }
            if(v[i + 2].S == 0){
                swap(v[i + 2], v[sz(v) - 1 - offset]);
                offset++;
            }
        }
    }
    p(ans, endl);
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