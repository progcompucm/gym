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

    priority_queue<ll> pq;
    each(&h : m) pq.push(h.S);

    ll ans = 0;
    while(sz(pq) >= 3){ 
        ll a = pq.top();
        pq.pop();
        ll b = pq.top();
        pq.pop();
        ll c = pq.top();
        pq.pop();
        ans++;

        if(a > 1) pq.push(a - 1);
        if(b > 1) pq.push(b - 1);
        if(c > 1) pq.push(c - 1);
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