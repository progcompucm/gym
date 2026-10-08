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

    vector<char> alph;
    map<ll, ll> char_idx;
    for(ll i = 0; i <= 25; i++){
        char c = 'a' + i;
        char_idx[c] = i;
        alph.pb(c);
    }

    vll r(n);
    vector<string> p(n);
    each(&x : r) cin >> x;
    each(&x : p) cin >> x;

    string target = "regalo";
    sort(all(target));

    rep(i, 0, n){
        string s;
        each(c : p[i]){
            ll idx = (char_idx[tolower(c)] - r[i] + 26) % 26;
            s += alph[idx];
        }
        sort(all(s));
        if(target == s){
            cout << i << "\n";
            break;
        }
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