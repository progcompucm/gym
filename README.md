# STL 
| Container | Methods  |
| :--- | :---: | 
| vector<T> | push_back, pop_back, back, resize, assign, insert, erase | 
| deque<T> | push_front, back, pop_front, back, [] |
| queue<T> | push, pop, front, empty |
| stack<T> | push, pop, top |
| priority_queue<T> | push, top, pop |
| set<T>, multiset<T> | insert, erase, find, count, lower_bound, upper_bound, begin, rbegin |
| map<K, V> | [], find, count, erase, lower_bound |
| unordered_map / map | insert, find, count, erase, reserve |
| string | substr, find, compare, stoi, to_string |

| Algorithms | Qué hace  |
| :--- | :---: | 
| sort(all(v)) | ... |
| lower_bound(all(v), x) | first element >= x |
| upper_bound(all(v), x) | first element > x |
| binary_search(all(v), x) | exists x? |
| reverse(all(x)) | ... |
| unique(all(v)) | elimina consecutivos repetidos |
| min_element | ... |
| max_element | ... |
| accumulate(all(v), 0LL) | Sum |
| count(all(v), x)/count_if | ... |
| find(all(v), x) | First x |
| any_of / all_of / none_of | ... |
| swap(a, b) | ... |
| gcd(a, b) | ... |
| lcm(a, b) | ... |
| is_sorted | ... |
| shuffle(all(v), rng) / mt19937 rng(time(0)) | ... |

| Algorithms | Qué hace  |
| :--- | :---: | 
| s.substr(pos, len) | ... |
| s.find(t) / s.rfind(t) | pos or string::npos |
| stoi, stoll, stod | ... |
| isdigit, isalpha, islower, toupper, tolower | ... |

# Base Template
```cpp
#include <bits/stdc++.h>
using namespace std;

const ll INF = LLONG_MAX / 4;

using ll = long long;
using vll = vector<ll>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvll = vector<vll>;

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
    vvll adj;

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
    vector<bool> vis(sz(adj), false);
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
    /*for(ll i = 0; i < N; i++){
        if(vis[i]) continue;
        if(dfs(i, vis, -1)) return true;
    }*/
    return dfs(0, vis, -1);
}
```

### Check for bipartite (Struct impl)
```cpp
bool is_bipartite(){
    vll color(N, -1);
    for(ll root = 0; root < N; root++){
        if(color[root] != -1) continue;
        queue<ll> q;
        q.push(root);
        color[root] = 0;
        while(!q.empty()){
            ll u = q.front();
            q.pop();
            for(ll v : adj[u]){
                if(color[v] == -1){
                    color[v] = 1 - color[u];
                    q.push(v);
                }else if(color[v] == color[u]){
                    return false;
                }
            }
        }
    }
    return true;
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

### Dijkstra (Struct impl using priority_queue)
```cpp
ll dijkstra(vvpll &adj, ll src, ll dest){
    vll dist(N, LLONG_MAX);
    dist[src] = 0;
    priority_queue<pll, vpll, greater<pll>> pq;
    pq.push({ 0, src });
    
    while(!pq.empty()){
        auto [d, u] = pq.top(); 
        pq.pop();
        if(d != dist[u]) continue; 
        if(u == dest) return d;
        for(auto [v, w] : adj[u]){
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({ dist[v], v });
            }
        }
    }
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

### Bellman-Ford (Negative weights) (Edge-struct-based Graph struct impl)
```cpp
struct Edge{
    ll u, v, w;
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

### Topological Sort
Se aplica a un grafo dirigido sin ciclos (DAG). Es una forma de ordenar los nodos de modo que
para cada arista u -> v, u aparezca antes que v.
Ejemplo: cursos con prerequisitos.
    - Álgebra -> Cálculo -> Física.
    - Programación -> Estructura de Datos.
Cómo:
    - Calcula el grado de entrada de cada nodo.
    - Mete a una cola los nodos con grado 0, que no dependen de nadie.
    - Saca uno, agregalo al orden y restale 1 al grado de sus vecinos. Los que lleguen a 0 entran a la cola.
    - Si al final procesmos menos de n nodos, hay un ciclo y el orden es imposible (por ejemplo A necesita B y B necesita A). 
Para:
    - Detectar ciclos grafos dirigidos.
    - Planificar tareas con dependencias.
```cpp
vll topological_sort(vvll &adj, ll n){
    vll indeg(n, 0);
    for(ll u = 0; u < n; u++) {
        for(ll v : adj[u]) indeg[v]++;
    }
    queue<ll> q;
    for(ll i = 0; i < n; i++) if(indeg[i] == 0) q.push(i);
    vll topo;
    while(!q.empty()) {
        ll u = q.front(); q.pop();
        topo.pb(u);
        for(ll v : adj[u]) {
            if(--indeg[v] == 0) q.push(v);
        }
    }
    return topo.size() == n ? topo : vll(); 
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

    // dfs(root, root)
    void dfs(ll node, ll parent){
        p[node] = parent;
        if(node == parent) dep[node] = 0;
        else dep[node] = dep[parent] + 1;
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

    // dfs(root, root) first 
    void dfs(ll node, ll parent){
        up[node][0] = parent;
        dep[node] = node == parent ? 0 : dep[parent] + 1;

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

## Tree Diameter (biggest dist/path of any two nodes in the tree)
```cpp
ll diameter(vvll& adj){
    ll n = adj.size();
    auto bfs = [&](ll src){
        vll dist(n, -1);
        queue<ll> q;
        q.push(src);
        dist[src] = 0;
        while(!q.empty()){
            ll u = q.front();
            q.pop();
            for(ll v : adj[u]){
                if(dist[v] != -1) continue;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
        return dist;
    };
    vll dist = bfs(0);
    ll A = max_element(all(dist)) - dist.begin();
    dist = bfs(A);
    return *max_element(all(dist));
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

# DSU
Es una estructura que mantiene grupos de elementos y responde dos preguntas:
- find(x): ¿en qué grupo está x?
- unite(a, b): junta los grupos de a y b.
Ejemplo: tenemos ciudades 1..5 y vamos leyendo carreteras:
- Carretera 1-2: unite(1, 2) -> grupos {1, 2}, {3}, {4}, {5}
- Carretera 4-5: unite(4, 5) -> grupos {1, 2}, {3}, {4, 5}
- ¿Están 1 y 5 conectadas? find(1) != find(5) => no.
Sirve para:
- Saber si dos nodos están conectados sin hacer un BFS cada vez.
- Contar componentes conexas mientras se agregan aristas (Road Construction).
```cpp
struct DSU{
    vll p, sz;
    ll comps;
    DSU(ll n) : p(n), sz(n, 1), comps(n){ iota(all(p), 0); }

    ll find(ll x){
        return p[x] == x ? x : p[x] = find(p[x]); 
    }

    bool unite(ll a, ll b){
        a = find(a), b = find(b);
        if(a == b) return false;
        if(sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        comps--;
        return true;
    }
};
```

# Kruskal
Dado un grafo con pesos, elegir las aristas que conectan todos los nodos con el menor costo total sin formar ciclos.
Ejemplo: construir carreteras que conecten todas las ciudades gastando lo minimo. Kruskal siempre toma la más barata que aún aporte una conexión nueva. 
Grafo conexo: Un grafo no dirigido es conexo si desde cualquier nodo podemos llegar a cualquier otro siguiendo aristas. Es decir que todo esta en una sola pieza. Un unico componente. 
```cpp
ll kruskal(ll n, vector<Edge>& e){
    sort(all(e), [](const Edge& a, const Edge& b){ return a.w < b.w; });
    DSU d(n);
    ll total = 0;
    for(auto& [u, v, w] : e){
        if(d.unite(u, v)) total += w;
    }
    return d.comps == 1 ? total : -1;
}
```

# Segment Tree
## Base Impl
```cpp
// vll v = {1, 2, 3, 4, 5, 6, 7, 8};
// SegTree tree(sz(v));
// tree.build(v);
// p(tree.query(0, 4)) => 15.
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
```

# Dynamic Programming
## Longest Common Subsequence
```cpp
// a = [1, 7, 1, 8, 3, 6, 5, 9]
// b = [7, 3, 9, 8]
// ans => 3 => 7, 3, 9
ll lcs(string a, string b){
    ll n = a.size(), m = b.size();
    vector<vll> dp(n + 1, vll(m + 1, 0));
    for(ll i = 1; i <= n; i++){
        for(ll j = 1; j <= m; j++){
            if(a[i - 1] == b[j - 1]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }else{
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}
```

## Longest Increase Subsequence
```cpp
ll lis(vll& a){
    vll dp;
    for(ll x : a){
        // if non-decreasing => upper_bound
        auto it = lower_bound(all(dp), x);
        if(it == dp.end()) dp.push_back(x);
        else *it = x;
    }
    return dp.size();
}
```

## Hamiltonian Path (number of routes for n)
```cpp
// Cantidad de caminos de 0 a n-1 que pasan por todos los nodos. n <= 20.
// in[v] = mascara de nodos u con arista u -> v
ll hamiltonian_paths(vvll &adj, ll n) {
    const ll MOD = 1e9+7;
    vector<vll> dp(1 << n, vll(n, 0));
    dp[1][0] = 1;
    
    for(ll mask = 1; mask < (1 << n); mask++) {
        if(!(mask & 1)) continue;
        for(ll last = 0; last < n; last++) {
            if(!(mask & (1 << last))) continue;
            if(dp[mask][last] == 0) continue;
            for(ll nxt : adj[last]) {
                if(mask & (1 << nxt)) continue;
                dp[mask | (1 << nxt)][nxt] = 
                    (dp[mask | (1 << nxt)][nxt] + dp[mask][last]) % MOD;
            }
        }
    }
    return dp[(1 << n) - 1][n - 1]; 
}
```

# Common Algorithms
## Longest Subarray (Two Pointers / Sliding Window)
```cpp
// Only works when a[i] >= 0
ll longest_subarr(vll& a, ll k){
    ll l = 0, sum = 0, ans = 0;
    for(ll r = 0; r < a.size(); r++){
        sum += a[r];
        while(sum > k){
            sum -= a[l];
            l++;
        }
        if(sum == k) ans = max(ans, r - l + 1);
    }
    return ans;
}
```

## Palindromic Substrings
```cpp
ll count_palindromic_substrings(string s){
    ll n = s.size();
    ll ans = 0;

    auto expand = [&](ll l, ll r){
        while(l >= 0 && r < n && s[l] == s[r]){
            ans++;
            l--;
            r++;
        }
    };

    for(ll i = 0; i < n; i++){
        expand(i, i);
        expand(i, i + 1);
    }

    return ans;
}
```

## Reverse Words
```cpp
string rev_words(string s){
    reverse(s.begin(), s.end());
    ll l = 0;
    for(ll r = 0; r <= s.size(); r++){
        if(r == s.size() || s[r] == ' '){
            reverse(s.begin() + l, s.begin() + r);
            l = r + 1;
        }
    }
    return s;
}
```

## Fast Mod
```cpp
ll fast_mod(ll a, ll b, ll mod){
    ll ans = 1;
    while(b > 0){
        if(b & 1) ans = (__int128)ans * a % mod;
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return ans;
}
```

## Largest Rectangle
```cpp
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
```

## Longest Consecutive Numbers
```cpp
ll longest_consecutive_numbers(vll& a){
    unordered_set<ll> st(all(a));
    ll ans = 0;
    for(ll x : st){
        if(!st.count(x - 1)){
            ll curr = x;
            ll len = 1;
            while(st.count(curr + 1)){
                curr++;
                len++;
            }
            ans = max(ans, len);
        }
    }
    return ans;
}
```

## Max Sum Subarray
```cpp
ll max_subarray_sum(vll& a){
    ll curr = a[0];
    ll ans = a[0];

    for(ll i = 1; i < a.size(); i++){
        curr = max(a[i], curr + a[i]);
        ans = max(ans, curr);
    }
    
    return ans;
}
```

## Lee Algorithm
```cpp
/**
S . . # . .
. # . # . .
. # . . . .
. # # # # .
. . . . . E

0 = camino
1 = obstáculo
S = (0,0)
E = (4,5)

Camino minimo: S → ↓ → ↓ → → → ↓ → → → E
*/
ll lee(vector<vll>& grid, pll start, pll end){
    ll n = grid.size();
    ll m = grid[0].size();
    
    vector<vll> dist(n, vll(m, -1));
    queue<pll> q;
    q.push(start);
    dist[start.F][start.S] = 0;

    ll dx [] = {-1, 1, 0, 0};
    ll dy[] = {0, 0, -1, 1};
    while(!q.empty()){
        auto [x, y] = q.front();
        q.pop();

        for(ll d = 0; d < 4; d++){
            ll nx = x + dx[d];
            ll ny = y + dy[d];
            
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(grid[nx][ny] == 1) continue;
            if(dist[nx][ny] != -1) continue;

            dist[nx][ny] = dist[x][y] + 1,
            q.push({ nx, ny });
        }
    }

    return dist[end.F][end.S];
}
```

## Counting Rooms
```cpp
ll count_rooms(vector<string>& g){
    ll n = len(g), m = len(g[0]), ans = 0;
    ll dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
    rep(i, 0, n) rep(j, 0, m){
        if(g[i][j] != '.') continue;
        ans++;
        vpll st = {{i, j}};
        g[i][j] = '#';
        while(!st.empty()){
            auto [x, y] = st.back(); 
            st.pop_back();
            rep(d, 0, 4){
                ll nx = x + dx[d], ny = y + dy[d];
                if(nx < 0 || nx >= n || ny < 0 || ny >= m || g[nx][ny] != '.') continue;
                g[nx][ny] = '#';
                st.pb({nx, ny});
            }
        }
    }
    return ans;
}
```