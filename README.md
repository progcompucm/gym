# Base Template
```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;

#define F first
#define S second
#define pb push_back

#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())

#define rep(i, a, b) for(ll i = (a); i < (b); i++)

template <typename T, typename... V>
void p(T&& t, V&&... v){
    cout << t;
    ((cout << ' ' << v), ...);
    cout << '\n';
}
```

# Graph 
## BFS
```cpp
void bfs(vector<vll>& adj, ll root_node){
    vector<bool> vis(adj.size(), false);
    queue<ll> q;
    q.push(root_node);
    vis[root_node] = true;
    while(!q.empty()){
        ll u = q.front();
        q.pop();
        for(ll v : adj[u]){
            if(vis[v]) continue;
            vis[v] = true;
            q.push(v);
        }
    }
}
```