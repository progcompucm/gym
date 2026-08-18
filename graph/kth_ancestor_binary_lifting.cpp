#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Graph {
    int n;
    int max_log;
    
    unordered_map<T, int> val_to_id;
    vector<T> id_to_val;
    
    vector<vector<int>> adj;
    vector<int> in_degree;
    vector<int> depth;
    vector<vector<int>> up;

    Graph() : n(0), max_log(0) {}

    int get_or_create_id(T val) {
        if (val_to_id.find(val) == val_to_id.end()) {
            val_to_id[val] = n;
            id_to_val.push_back(val);
            adj.push_back({});
            in_degree.push_back(0);
            n++;
        }
        return val_to_id[val];
    }

    void add_edge(T u_val, T v_val) {
        int u = get_or_create_id(u_val);
        int v = get_or_create_id(v_val);
        adj[u].push_back(v);
        in_degree[v]++;
    }

    void init_binary_lifting() {
        if (n == 0) return;
        max_log = log2(n) + 2;
        depth.assign(n, 0);
        up.assign(n, vector<int>(max_log, 0));
        
        int root = 0;
        for (int i = 0; i < n; ++i) {
            if (in_degree[i] == 0) {
                root = i;
                break;
            }
        }
        dfs(root, root);
    }

    void dfs(int u, int p) {
        up[u][0] = p;
        for (int i = 1; i < max_log; ++i) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (int v : adj[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }
        }
    }

    T get_kth_ancestor(T node_val, int k) {
        if (val_to_id.find(node_val) == val_to_id.end()) return T();
        int node = val_to_id[node_val];
        if (k > depth[node]) return T();
        for (int i = 0; i < max_log; ++i) {
            if ((k >> i) & 1) {
                node = up[node][i];
            }
        }
        return id_to_val[node];
    }

    void print_graph() {
        for (int i = 0; i < n; ++i) {
            cout << "Nodo " << id_to_val[i] << " -> ";
            for (int v : adj[i]) {
                cout << id_to_val[v] << " ";
            }
            cout << "\n";
        }
    }
};

int main() {
    Graph<int> g;

    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(3, 4);
    g.add_edge(3, 5);

    g.init_binary_lifting();
    g.print_graph();

    return 0;
}
