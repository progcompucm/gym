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

// TODO: DEBUG THIS!!!
void solve(){
    ll N, S, K;
    cin >> N >> S >> K;

    vll h(N), l(N), u(N);
    rep(i, 0, N){
        cin >> h[i] >> l[i] >> u[i];
    }

    // 10 ^ 5
    const ll MAX = 100000;
    vll A(MAX + 1, 0), B(MAX + 1, 0);
    ll total = 0;

    auto update = [&](ll i, ll sign){
        ll cap = K / h[i];
        total += sign * cap;
        for(ll x = h[i]; x <= MAX; x += x & -x){
            A[x] += sign * cap;
            B[x] += sign * cap * h[i];
        }
    };

    vll byL(N), byU(N);
    rep(i, 0, N) byL[i] = byU[i] = i;

    sort(all(byL), [&](ll a, ll b){
        return l[a] * h[b] < l[b] * h[a];
    });

    sort(all(byU), [&](ll a, ll b){
        return u[a] * h[b] < u[b] * h[a];
    });

    bool found = false;
    ll best_num = 0, best_den = 1;
    ll pa = 0, pr = 0;

    rep(k, 0, N){
        ll c = byL[k];
        ll num = l[c];
        ll den = h[c];

        // in: l/h <= pmin
        while(pa < N && l[byL[pa]] * den <= num * h[byL[pa]]){
            update(byL[pa], +1);
            pa++;
        }

        // out: u/h < pmin
        while(pr < N && u[byU[pr]] * den < num * h[byU[pr]]){
            update(byU[pr], -1);
            pr++;
        }

        if(total < S) continue;

        // descent via the Fenwick... highest pos with cap prefix < S
        ll pos = 0;
        ll rem = S;
        ll f = 0;
        for(ll j = 16; j >= 0; j--){
            ll np = pos + (1LL << j);
            if(np <= MAX && A[np] < rem){
                pos = np;
                rem -= A[np];
                f += B[np];
            }
        }

        f += rem * (pos + 1);
        ll cost_num = num * f;
        ll cost_den = den;
        if(!found || cost_num * best_den < best_num * cost_den){
            found = true;
            best_num = cost_num;
            best_den = cost_den;
        }
    }

    if(!found){
        cout << "*\n";
        return;
    }

    ll g = __gcd(best_num, best_den);
    cout << best_num / g << " " << best_den / g << "\n";
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