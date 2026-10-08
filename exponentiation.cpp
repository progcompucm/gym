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
    ll a, b;
    cin >> a >> b;

    if(a == 0 && b == 0){
        cout << 1 << endl;
    }else if(a == 0){
        cout << 0 << endl;
    }else if(b == 0){
        cout << 1 << endl;
    }else{
        ll ans = 1, m = 1000000007;
        vll v;
        while(b != 1){
            if(b % 2 == 0){
                v.pb(0);
                b /= 2;
            }else{
                v.pb(1);
                b -= 1;
            }
        }

        v.pb(1);
        for(ll i = sz(v) - 1; i >= 0; i--){
            if(v[i] == 0){
                ans = ((ans % m) * (ans % m)) % m;
            }else{
                ans = ((ans % m) * (a % m)) % m;
            }
        }
        cout << ans << endl;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    ll n;
    cin >> n;
    while(n--) solve();

    return 0;
}   