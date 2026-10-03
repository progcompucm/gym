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

void solve(){

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

### Can be useful...
```cpp
// vector<string> cities = {"Delhi", "London", "Paris", "New York"};
// Graph g(cities);
// g.add_edge("Delhi", "London"); ...
class Node{
public:
    string name;
    list<string> nbrs;
    Node(string n) name(n){}
};

class Graph{
    unordered_map<string, Node*> m;
public:
    Graph(vector<string> n){
        for(string v : n){
            m[v] = new Node(v);
        }
    }

    void add_edge(string u, string v){
        m[u]->nbrs.push_back(v);
        m[v]->nbrs.push_back(u);
    }

    void print(){
        for(auto x : m){
            cout << x.first << " -> ";
            for(auto v : x.second->nbrs){
                cout << v << " ";
            }
            cout << endl;
        }
    }
};
```

## Shortest Path Algorithms
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

### Floyd Warshall (Graph Impl Struct with Adjacency Matrix needed)
```cpp
struct Graph{
    ll N;
    vvll adj;

    Graph(ll n): N(n), adj(n, vll(n, LLONG_MAX)){
        for(ll i = 0; i < N; i++) adj[i][i] = 0;
    }

    vvll floyd_warshall(){
        vvll dist = adj;
        for(ll k = 0; k < N; k++){
            for(ll i = 0; i < N; i++){
                for(ll j = 0; j < N; j++){
                    if(dist[i][k] == LLONG_MAX || dist[k][j] == LLONG_MAX) continue;
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        return dist;
    }
}
```

### Floyd Warshall (Negative weights) (Edge-struct-based Graph struct impl)
```cpp
struct Edge{
    ll u, v w;
};

struct Graph{
    ll N;
    vector<Edge> e;
    Graph(ll n) : N(n){}

    void add_edge(ll u, ll v, ll w){
        e.push_back({ u, v, w });
    }

    vll bellman_ford(ll src){
        vll dist(N, LLONG_MAX);
        dist[src] = 0;
        for(ll i = 0; i < N - 1; i++){
            for(auto [u, v, w] : e){
                if(dist[u] == LLONG_MAX) continue;
                dist[v] = min(dist[v], dist[u] + w);
            }
        }
        return dist;
    }
}
```

# Tree
## All Ancestors 
```cpp
void dfs(ll node, ll parent, vvll& adj, vll& parent_node){
    parent_node[node] = parent;
    for(ll v : adj[node]){
        if(v == parent) continue;
        dfs(v, node, adj, parent_node);
    }
}

vll get_path(ll from, ll to, ll n, vvall& adj){
    vll parent(n, -1);
    dfs(from, -1, adj, parent);
    vll path;
    while(to != -1){
        path.pb(to);
        if(to == from) break;
        to = parent[to];
    }
    reverse(all(path));
    return path;
}
```

## Lowest Common Ancestor (LCA Struct impl)
```cpp
struct Graph{
    ll N;
    vvll adj;
    vll p, dep;

    Graph(ll n): N(n), p(n, -1), dep(n, 0), adj(n){}

    void add_edge(ll u, ll v){
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void dfs(ll node, ll parent){
        p[node] = parent;
        dep[node] = dep[parent] + 1;
        for(ll v : adj[node]){
            if(v == parent) continue;
            dfs(v, node);
        }
    }

    ll lca(ll u, ll v){
        if(u == v) return u;
        // depth of u is more than depth of v,
        // avoid 2 cases:
        if(dep[u] < dep[v]) swap(u, v);
        ll diff = dep[u] - dep[v];

        // depth of both nodes same
        while(diff--) u = p[u];

        // until they're equal nodes keep climbing
        while(u != v){
            u = p[u];
            v = p[v];
        }
        return u;
    }
};
```

## LCA using binary lifting (Custom Struct impl)
```cpp
struct Graph{
    ll N, LOG;
    vvll adj, up;
    vll dep;

    Graph(ll n) : 
        N(n),
        LOG(log2(n) + 1), 
        up(n, vll(LOG, 0)), 
        dep(n, 0), 
        adj(n){}

    void add_edge(ll u, ll v){
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void dfs(ll node, ll parent){
        up[node][0] = parent;
        dep[node] = dep[parent] + 1;

        for(ll i = 1; i < LOG; i++){
            up[node][i] = up[up[node][i - 1]][i - 1];
        }

        for(ll v : adj[node]){
            if(v == parent) continue;
            dfs(v, node);
        }
    }

    ll lca(ll u, ll v){
        if(dep[u] < dep[v]) swap(u, v);
        ll diff = dep[u] - dep[v];

        for(ll i = 0; i < LOG; i++){
            if(diff & (1LL << i)) u = up[u][i];
        }

        if(u == v) return u;
        for(ll j = LOG - 1; j >= 0; j--){
            if(up[u][j] != up[v][j]){
                u = up[u][j];
                v = up[v][j];
            }
        }
        
        return up[u][0];
    } 
}
```

## Symmetric Tree
```cpp
// Node* root = new Ndde(...);
// root->left = new Node(...);
// root->left->left = new Node(...);
struct Node{
    ll val;
    Node* left;
    Node* right;

    Node(ll v): val(v), left(nullptr), right(nullptr){}
};

bool is_mirror(Node* a, Node *b){
    if(a == nullptr && b == nullptr) return true;
    if(a == nullptr || b == nullptr) return false;
    if(a->val != b->val) return false;
    return is_mirror(a->left, b->right) && is_mirror(a->right, b->left);
}

bool is_symmetric(Node* root){
    if(root == nullptr) return true;
    return is_mirror(root->left, root->right);
}
```