#include <bits/stdc++.h>
using namespace std;

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
    Graph<> g(5, true);

    g.add_edge(0, 1);
    g.add_edge(1, 2);

    return 0;
}