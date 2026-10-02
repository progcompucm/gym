#include<bits/stdc++.h>
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
#define sz(x) x.size()
#define all(x) x.begin(), x.end()
#define endl "\n"

int maximalNetworkRank(int n, vector<vector<int>> roads) {
    vector<vll> adj(n);

    for(auto r : roads){
        ll u = r[0], v = r[1];
        adj[u].pb(v);
        adj[v].pb(u);
    }

    ll max_rank = 0;
    for(ll u = 0; u < n; u++){
        for(ll v = u + 1; v < n; v++){
            ll rank = sz(adj[u]) + sz(adj[v]);

            // check if u & b are connected
            bool conn = false;
            for(ll x : adj[u]){
                if(x == v){
                    conn = true;
                    break;
                }
            }
            if(conn) rank--;
            max_rank = max(rank, max_rank);
        }
    }

    return max_rank;
}

int main(){
    vector<vector<int>> roads = {
        {0, 1}, {0, 3}, {1, 2}, {1, 3}
    };
    cout << maximalNetworkRank(4, roads);
    return 0;
}