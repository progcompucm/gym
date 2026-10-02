#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vll vector<ll>
#define pb push_back

template <typename T, typename... V>
void p(T&& t, V&&... v){
    cout << t;
    initializer_list<int>{ (cout << ' ' << v, 0)... };
    cout << endl;
}

void dfs_helper(ll node, vector<bool>& vis, vector<vll>& adj){
    vis[node] = true;
    p("dfs_helper - node:", node);
    // make a dfs call on all its unvisited neighbors
    for(ll v : adj[node]){
        if(vis[v]) continue;
        vis[v] = true;
        p("    recursive_call for neigh", v, "of node", node);
        dfs_helper(v, vis, adj);
    }
}

void dfs(vector<vll>& adj, ll N, ll root_node){
    vector<bool> vis(N, false);
    p("root_node:", root_node);
    dfs_helper(root_node, vis, adj);
}

int main(){
    vector<vll> adj(7);
    adj[0].pb(1);
    adj[1].pb(0);

    adj[1].pb(2);
    adj[2].pb(1);

    adj[3].pb(5);
    adj[5].pb(3);

    adj[5].pb(6);
    adj[6].pb(5);

    adj[4].pb(5);
    adj[5].pb(4);

    adj[0].pb(4);
    adj[4].pb(0);

    adj[3].pb(4);
    adj[4].pb(3);

    dfs(adj, 7, 0);
    return 0;
}