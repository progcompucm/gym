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
#define sz(x) ((ll)) x.size()
#define all(x) x.begin(), x.end()
#define endl "\n"

int findCenter(vector<vector<int>> edges){
    map<ll, vll> g;
    for(auto e : edges){
        g[e[0]].push_back(e[1]);
        g[e[1]].push_back(e[0]);
    }
    
    for(auto u : g){
        if(u.second.size() == edges.size()){
            return (int)u.first;
        }
    }

    return -1;
}

int main(){
    vector<vector<int>> edges = {
        {1, 2}, {2, 3}, {4, 2}
    };
    cout << findCenter(edges) << "\n";
    
    return 0;
}