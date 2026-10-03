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

struct SegTree{
    vll st;
    ll N;

    SegTree(ll n) : N(n), st(4 * n, 0){}

    void build(ll start, ll end, ll node, vll& v){
        // leaf node base case
        if(start == end){
            st[node] = v[start];
            return;
        }

        ll mid = (start + end) / 2;
        // left subtree is (start, mid)
        build(start, mid, 2 * node + 1, v);

        // right subtree is (mid + 1, end)
        build(mid + 1, end, 2 * node + 2, v);
        
        st[node] = st[node * 2 + 1] + st[node * 2 + 2];
    }

    ll query(ll start, ll end, ll l, ll r, ll node){
        // non overlapping case
        if(start > r || end < l) return 0;
        
        // complete overlap
        if(start >= l && end <= r) return st[node];

        // partial case
        ll mid = (start + end) / 2;
        ll q1 = query(start, mid, l, r, 2 * node + 1); 
        ll q2 = query(mid + 1, end, l, r, 2 * node + 2);
        return q1 + q2;  
    }
    
    ll query(ll l, ll r){
        return query(0, N - 1, l, r, 0);
    }

    void build(vll& v){
        build(0, N - 1, 0, v);
    }
};

void solve(){
    vll v = {1, 2, 3, 4, 5, 6, 7, 8};

    SegTree tree(v.size());
    tree.build(v);
    p(tree.query(0, 4));
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    
    ll t;
    cin >> t;
    while(t--) solve();

    return 0;
}