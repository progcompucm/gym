# Base Template
```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvll = vector<vll>

#define F first
#define S second
#define pb push_back

#define all(x) (x).begin(), (x).end()
#define len(x) ((ll)(x).size())

#define rep(i, a, b) for(ll i = (a); i < (b); i++)

template <typename T, typename... V>
void p(T&& t, V&&... v){
    cout << t;
    ((cout << ' ' << v), ...);
    cout << '\n';
}
```

# Graph 
## If struct is needed
```cpp
struct Graph{
    ll N;
    // or vector<vpll> adj => adj[u].pb({ v, w })
    vvall adj;

    Graph(ll n) : N(n), adj(n){}

    void add_edge(ll u, ll v){
        adj[u].pb(v);
        adj[v].pb(u);
    }
}
```

## BFS
### Base Idea
```cpp
void bfs(vvll& adj, ll root_node){
    vector<bool> vis(len(adj), false);
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

### BFS for compute dists and parents
```cpp
void bfs(vvll& adj, ll root_node, ll N){
    vll dist(N, -1);
    vll parent(N, -1);
    queue<ll> q;
    q.push(root_node);
    parent[root_node] = root_node;
    dist[root_node] = 0;
    while(!q.empty()){
        ll u = q.front();
        q.pop();
        for(ll v : adj[u]){
            if(dist[v] != -1) continue;
            q.push(v);
            parent[v] = u;
            dist[v] = dist[u] + 1;
        }
    }
}
```

### Showing the path using the parent arr
```cpp
ll temp = dest;
while(temp != root_node){
    cout << temp << " -- ";
    temp = parent[temp];
}
cout << root_node << "\n";
```

### Cycle Detection (Struct impl)
```cpp
bool has_cycle(ll root_node){
    vll parent(N, -1);
    queue<ll> q;
    parent[root_node] = root_node;
    q.push(root_node);
    while(!q.empty()){
        ll u = q.front();
        q.pop();
        for(ll v : adj[u]){
            if(parent[v] == -1){
                parent[v] = u;
                q.push(v);
            }else if(v != parent[u]){
                return true;
            }
        }
    }
    return false;
}
```

## DFS
### Base Idea
```cpp
void dfs_helper(ll node, vector<bool>& vis, vvll& adj){
    vis[node] = true;
    // make a dfs call on all its unvisited nbrs
    for(ll v : adj[node]){
        if(vis[v]) continue;
        vis[v] = true;
        dfs_helper(v, vis, adj);
    }
}

void dfs(vvll& adj, ll N, ll root_node){
    vector<bool> vis(N, false);
    dfs_helper(root_node, vis, adj);
}
```

### Cycle Detection (Struct impl)
```cpp
bool dfs(ll node, vector<bool>& vis, ll parent){
    vis[node] = true;
    for(ll v : adj[node]){
        if(!vis[v]){
            vis[v] = true;
            bool nbr_found_cycle = dfs(v, vis, node);
            if(nbr_found_cycle) return true;
            continue;
        }
        if(v != parent) return true;
    }
    return false;
}

bool has_cycle(){
    vector<bool> vis(N, false);
    return dfs(0, vis, -1);
}
```

### Dijkstra (Struct impl)
```cpp
ll dijkstra(ll src, ll dest){
    vll dist(N, LLONG_MAX);
    set<pll> s;
    vll parent(N, -1);

    dist[src] = 0;
    s.insert({ 0, src });

    while(!s.empty()){
        auto it = s.begin();
        ll node = it->second;
        ll curr_dist = it->first;
        s.erase(it);

        for(auto [v, w] : adj[node]){
            if(curr_dist + w < dist[v]){
                // remove if neighbor already exists in the set
                auto f = s.find({ dist[v], v });
                if(f != s.end()) s.erase(f);

                // insert the updated value with the new dist
                dist[v] = curr_dist + w;
                parent[v] = node;
                s.insert({ dist[v], v });
            }
        }
    }

    // if path is required
    vll path;
    ll temp = dest;
    while(temp != -1){
        path.pb(temp);
        temp = parent[temp];
    }
    reverse(all(path));

    return dist[dest];
}
```