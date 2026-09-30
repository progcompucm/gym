#include <bits/stdc++.h>
using namespace std;

#define ll long long

template <typename W = int>
struct Graph {
    struct Edge {
        int to;
        W weight;
    };

    int n;
    bool undirected;
    bool weighted;

    vector<vector<Edge>> adj;

    Graph(int n, bool undirected = false, bool weighted = false)
        : n(n),
          undirected(undirected),
          weighted(weighted),
          adj(n) {}

    void add_edge(int u, int v, W w = W(1)) {
        adj[u].push_back({v, weighted ? w : W(1)});

        if (undirected) adj[v].push_back({u, weighted ? w : W(1)});
    }

    void print_graph() {
        for (int u = 0; u < n; ++u) {
            cout << u << " -> ";
            for (const auto& edge : adj[u]) {
                cout << edge.to;
                if (weighted) cout << "(" << edge.weight << ")";
                cout << " ";
            }

            cout << '\n';
        }
    }
};

int main(){
    ll n, m;
    cin >> n >> m;

    vector<string> mp(n);
    for(auto &x : mp) cin >> x;

    Graph<ll> g(n * m);
    ll dr[4] = {-1, 1, 0,  0}, dc[4] = {0, 0, -1, 1};

    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < m; j++){
            if(mp[i][j] == '#') continue;
            ll u = i * m + j;

            for(int k = 0; k < 4; k++){
                ll ni = i + dr[k], nj = j + dc[k];
                if(ni >= 0 && ni < n && nj >= 0 && nj < m && mp[ni][nj] == '.'){
                    int v = ni * m + nj;
                    g.add_edge(u, v);
                }
            }
        }
    }

    vector<char> seen(n * m, 0);
    ll rooms = 0;
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < m; j++){
            ll u = i * m + j;
            if(mp[i][j] == '.' && !seen[u]){
                rooms++;
                queue<int> q;
                q.push(u);
                seen[u] = 1;
                
                while(!q.empty()){
                    int x = q.front();
                    q.pop();
                    for(auto v : g.adj[x]){
                        if(!seen[v.to]){
                            seen[v.to] = 1;
                            q.push(v.to);
                        }
                    }
                }
            }
        }
    }

    cout << rooms << "\n";

    // g.print_graph();

    return 0;
}