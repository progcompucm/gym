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
    ll n, x;
    cin >> n >> x;

    ll step_size = 70, step = 0;
    while(step <= 5000){
        step = min(step + step_size, n);
        p("? ", step, "\n");
        cout << flush;
        ll v;
        cin >> v;
        if(v >= x){
            p("R\n");
            cout << flush;  
            rep(i, max((ll)1, step - step_size), step + 1){
                p("? ", i, "\n");
                cout << flush;
                cin >> v;
                if(v == x){
                    p("! ", i, "\n");
                    cout << flush;
                    break;
                }
            }
            break;  
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
   
    solve();

    return 0;
}   