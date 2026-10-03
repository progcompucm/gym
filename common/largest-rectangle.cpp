#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define F first
#define S second
#define pb push_back
#define pll pair<ll, ll>
#define vll vector<ll>
#define mpll map<pll, ll> 
#define mll map<ll, ll>
#define vpp vector<pll, pll>
#define sz(x) ((ll)) x.size()
#define all(x) x.begin(), x.end()
#define endl "\n"

template <typename T, typename... V>
void p(T&& t, V&&... v){
    cout << t;
    initializer_list<int>{ (cout << ' ' << v, 0)... };
    cout << endl;
}

ll largest_rectangle(vll& h){
    ll n = h.size();
    stack<ll> st;
    ll ans = 0;

    for(ll i = 0; i <= n; i++){
        ll curr = (i == n ? 0 : h[i]);

        while(!st.empty() && h[st.top()] > curr){
            ll height = h[st.top()];
            st.pop();

            ll left = st.empty() ? -1 : st.top();
            ll width = i - left - 1;

            ans = max(ans, height * width);
        }

        if(i < n) st.push(i);
    }

    return ans;
}

void solve(){
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    
    ll t;
    // cin >> t;
    while(t--) solve();

    return 0;
}