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
    ll N, S, K;
    cin >> N >> S >> K;

    // {h, l u}
    vector<array<ll, 3>> v(N);
    rep(i, 0, N){
        cin >> v[i][0] >> v[i][1] >> v[i][2];
    }
    sort(all(v));

    bool found = false;
    ll best_l = 0, best_h = 1;
    rep(c, 0, N){
        // pmin = l[c] / h[c]
        ll num = v[c][1];
        ll den = v[c][0];
        ll streets = S;
        ll f = 0;

        rep(i, 0, N){
            ll h = v[i][0];
            ll l = v[i][1];
            ll u = v[i][2];
            ll p = num * h;
            if(p < l * den || p > u * den) continue;
            ll take = min(streets, K / h);
            f += take * h;
            streets -= take;
            if(streets == 0) break;
        }
        if(streets > 0) continue;

        ll cost_num = num * f;
        ll cost_den = den;
        
        if(!found || cost_num * best_h < best_l * cost_den){
            found = true;
            best_l = cost_num;
            best_h = cost_den;
        }
    }

    if(!found){
        cout << "*\n";
        return;
    }

    ll g = __gcd(best_l, best_h);
    cout << best_l / g << " " << best_h / g << "\n";
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